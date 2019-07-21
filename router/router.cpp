#include <router.hpp>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <ip_helpers.hpp>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cstring>
#include <unistd.h>

router::router()
  : sockfd_(socket(AF_INET, SOCK_DGRAM, 0)),
    current_round_(10)
{
  if (sockfd_ < 0)
    throw std::runtime_error(std::string("socket error ") + strerror(errno));

  int broadcastPermission = 1;
  if (setsockopt(sockfd_, SOL_SOCKET, SO_BROADCAST, (char*)&broadcastPermission, sizeof(broadcastPermission)))
    throw std::runtime_error(std::string("setsockopt SO_BROADCAST error ") + strerror(errno));

  sockaddr_in sin{};
  sin.sin_family = AF_INET;
  sin.sin_port = htons(54321);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sockfd_, (sockaddr*)&sin, sizeof(sin)))
    throw std::runtime_error(std::string("bind error ") + strerror(errno));
}

void router::add_local_network(const std::string& ip_mask, unsigned distance)
{
  auto ip_and_mask = ip_helpers::string_to_ip_and_mask(ip_mask);
  local_networks_.push_back(
  {
    ip_helpers::address_to_string(ip_helpers::make_network_address(ip_and_mask.first, ip_and_mask.second)) + '/' + std::to_string(ip_and_mask.second),
    ip_helpers::make_broadcast_address(ip_and_mask.first, ip_and_mask.second),
    ip_helpers::make_network_address(ip_and_mask.first, ip_and_mask.second),
    ip_helpers::make_my_address(ip_and_mask.first),
    ip_and_mask.second,
    distance,
    {}
  }
  );
}

void router::listen(unsigned seconds)
{
  ++current_round_;
  char buffer[IP_MAXPACKET + 1];
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(sender);
  timeval time_limit{};
  time_limit.tv_sec = seconds;

  while (1)
  {
    fd_set sockfd_set;
    FD_ZERO(&sockfd_set);
    FD_SET(sockfd_, &sockfd_set);
    int ready = select(sockfd_ + 1, &sockfd_set, NULL, NULL, &time_limit);

    if (ready == 0)
      return;

    if (ready == -1)
      throw std::runtime_error(std::string("select error ") + strerror(errno));

    auto datagram_len = recvfrom(sockfd_, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
    if (datagram_len < 0)
      throw std::runtime_error(std::string("recvfrom error ") + strerror(errno));
    if (datagram_len != 9)
      //throw std::runtime_error("datagram is not 9 bytes in length");
      continue;

    bool should_skip = false;
    //sprawdzam, czy to nie echo ode mnie
    for (const auto& lnet : local_networks_)
      if (*(unsigned*)&sender.sin_addr == *(unsigned*)&lnet.my_ip.sin_addr)
      {
        should_skip = true;
        break;
      }
    if (should_skip)
      continue;

    //htonl(remote_subnet_ip) == *(unsigned*)&lnet.my_ip.sin_addr 
    unsigned remote_subnet_ip;
    memcpy((char*)&remote_subnet_ip, buffer, 4);
    remote_subnet_ip = ntohl(remote_subnet_ip);
    unsigned char mask = *(unsigned char*)(buffer + 4);
    unsigned distance;
    memcpy((char*)&distance, buffer + 5, 4);
    distance = ntohl(distance);
    for (auto& lnet : local_networks_)
    {
      if (ip_helpers::belongs_to_subnet(lnet.subnet_address, sender, lnet.mask))
      {
        unsigned sender_ip = htonl(*(unsigned*)&sender.sin_addr);
        lnet.endpoint_to_last_reply[sender_ip] = current_round_;
        //jestem teraz w jednej lokalnej sieci
        //sprawdzam, czy on moze wyslal info o innej mojej lokalnej
        auto iter = std::find_if(local_networks_.begin(), local_networks_.end(), [remote_subnet_ip](const local_network & ln)
        {
          return ip_helpers::belongs_to_subnet(ln.subnet_address, ip_helpers::make_my_address(remote_subnet_ip), ln.mask);
        });
        if (iter != local_networks_.end())
          break;

        auto& remote = remote_networks_.ip_to_endpoint[remote_subnet_ip];
        remote.last_reply_round = current_round_;
	remote.mask = mask;
        if (remote.distance > distance || remote.distance == 0)
        {
          remote.accessible_by_ip = sender_ip;
          remote.distance = distance + lnet.distance;
        }}
    }
  }
}

void router::broadcast()
{
  for (auto& lnet : local_networks_)
  {
    for (auto& mynet : local_networks_)
    {
      char buffer[9];
      memcpy(buffer, (char*)&mynet.subnet_address.sin_addr.s_addr, 4);
      *(unsigned char*)(buffer + 4) = mynet.mask;
      unsigned distance_htonl =  htonl(mynet.distance);
      memcpy(buffer + 5, (char*)&distance_htonl, 4);
      if (sendto(sockfd_, buffer, 9, 0, (struct sockaddr*) &lnet.broadcast_address, sizeof(lnet.broadcast_address)) != 9)
        //throw std::runtime_error(std::string("sendto error ") + strerror(errno));
        for (auto& elem : lnet.endpoint_to_last_reply)
          elem.second = 0xFFFFFFFF;
    }
    for (const auto& r_pair : remote_networks_.ip_to_endpoint)
    {
      unsigned network = r_pair.first;
      const remote_network::endpoint& endpoint = r_pair.second;
      /*
      unsigned char mask;
      unsigned accessible_by_ip;
      long last_reply_round;
      unsigned distance;
      */
      if (endpoint.distance > 100)
        continue;
      char buffer[9];
      unsigned network_htonl = htonl(network);
      memcpy(buffer, (char*)&network_htonl, 4);
      *(unsigned char*)(buffer + 4) = endpoint.mask;
      unsigned distance_htonl = htonl(endpoint.distance);
      memcpy(buffer + 5, (char*)&distance_htonl, 4);
      if (sendto(sockfd_, buffer, 9, 0, (struct sockaddr*) &lnet.broadcast_address, sizeof(lnet.broadcast_address)) != 9)
        //throw std::runtime_error(std::string("sendto error ") + strerror(errno));
        for (auto& elem : lnet.endpoint_to_last_reply)
          elem.second = 0xFFFFFFFF;
    }
  }
}

void router::print()
{
  for (const auto& lnet : local_networks_)
  {
    std::cout << lnet.str_representtion;
    unsigned last_reply = 0;
    for (const auto& endpoint : lnet.endpoint_to_last_reply)
      if (endpoint.second > last_reply)
        last_reply = endpoint.second;
    if (last_reply + 5 < current_round_)
      std::cout << " unreachable connected directly\n";
    else
      std::cout << " distance " << lnet.distance << " connected directly\n";
  }
  for (const auto& rnet : remote_networks_.ip_to_endpoint)
  {
    std::cout << ip_helpers::address_to_string(ip_helpers::make_my_address(rnet.first)) << '/' << (unsigned)rnet.second.mask << " distance " << rnet.second.distance
              << " via " << ip_helpers::address_to_string(ip_helpers::make_my_address(rnet.second.accessible_by_ip)) << std::endl;
  }
  std::cout << std::endl;
}
