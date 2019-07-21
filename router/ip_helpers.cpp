#include <ip_helpers.hpp>
#include <arpa/inet.h>
#include <stdexcept>

namespace ip_helpers
{

std::pair<unsigned, unsigned char> string_to_ip_and_mask(const std::string& str)
{
  auto it = str.find_last_of('/');
  unsigned char mask = (unsigned char)std::stoul(str.substr(it + 1, str.size() - it - 1));
  auto ip = str.substr(0, it);
  unsigned net_ip;
  if (inet_pton(AF_INET, ip.c_str(), &net_ip) != 1)
    throw std::invalid_argument("Unable to convert IP to numeric form");
  return {htonl(net_ip), mask};
}

sockaddr_in make_broadcast_address(unsigned host_ip, unsigned char mask)
{
  sockaddr_in res{};
  res.sin_family = AF_INET;
  res.sin_port = htons(54321);
  unsigned subnet_mask = (~0u) >> mask;
  res.sin_addr.s_addr = htonl(host_ip | subnet_mask);
  return res;
}

sockaddr_in make_network_address(unsigned host_ip, unsigned char mask)
{
  sockaddr_in res{};
  res.sin_family = AF_INET;
  res.sin_port = htons(54321);
  unsigned subnet_mask = (~0u) << (32 - mask);
  res.sin_addr.s_addr = htonl(host_ip & subnet_mask);
  return res;
}

sockaddr_in make_my_address(unsigned host_ip)
{
  sockaddr_in res{};
  res.sin_family = AF_INET;
  res.sin_port = htons(54321);
  res.sin_addr.s_addr = htonl(host_ip);
  return res;
}

std::string address_to_string(const sockaddr_in& addr)
{
  char buf[20];
  inet_ntop(AF_INET, (void*)&addr.sin_addr, buf, sizeof(buf));
  return buf;
}

bool belongs_to_subnet(const sockaddr_in& subnet_addr, const sockaddr_in& foreign_addr, unsigned char mask)
{
  return ntohl(subnet_addr.sin_addr.s_addr) == (ntohl(foreign_addr.sin_addr.s_addr) & ((~0u) << (32 - mask)));
}

}
