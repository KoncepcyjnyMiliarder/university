/*
Krzysztof Pyrkosz
261282
*/
#include <transport.hpp>
#include <request_serializer.hpp>
#include <stdexcept>
#include <netinet/ip.h>
#include <cstring>
#include <arpa/inet.h>

void transport::receive()
{
  char buffer[IP_MAXPACKET + 1];
  sockaddr_in sender;
  socklen_t senderlen = sizeof(sender);
  timeval time_limit{};
  time_limit.tv_sec = 0;
  time_limit.tv_usec = 1000;

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

    auto datagram_len = recvfrom(sockfd_, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &senderlen);
    if (datagram_len < 0)
      throw std::runtime_error(std::string("recvfrom error ") + strerror(errno));
    unsigned start, size;
    const char* data;
    bool succ = request_serializer::dissect_response(buffer, datagram_len, &start, &size, &data);
    if (!succ)
      continue;
    cp_.on_chunk_received(start, size, data);
  }
}

void transport::request()
{
  auto res = cp_.get_wanted_chunk_and_size();
  if (res.second == 0)
    return;

  auto str = request_serializer::make_request_string(res.first, res.second);
  if (sendto(sockfd_, str.c_str(), str.size(), 0, (struct sockaddr*) &host_address_, sizeof(host_address_)) < 0)
    throw std::runtime_error(std::string("sendto error ") + strerror(errno));
}

transport::transport(const std::string& ip, unsigned short port, const std::string& out_filename, unsigned requested_size)
  : sockfd_(socket(AF_INET, SOCK_DGRAM, 0)),
    host_address_{},
    cp_(requested_size, out_filename)
{
  if (sockfd_ < 0)
    throw std::runtime_error(std::string("socket error ") + strerror(errno));

  //156.17.4.30
  host_address_.sin_family = AF_INET;
  host_address_.sin_port = htons(port);
  if (inet_pton(AF_INET, ip.c_str(), &(host_address_.sin_addr)) == 0)
    throw std::invalid_argument("Given string is not a valid IP address");
  sockaddr_in sin{};
  sin.sin_family = AF_INET;
  sin.sin_port = 0;
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sockfd_, (sockaddr*)&sin, sizeof(sin)))
    throw std::runtime_error(std::string("bind error ") + strerror(errno));
}

void transport::run()
{
  while (!cp_.is_finished())
  {
    receive();
    request();
  }
}
