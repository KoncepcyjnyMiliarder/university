#pragma once

#include <string>
#include <netinet/in.h>
#include <netinet/ip.h>

namespace ip_helpers
{
std::pair<unsigned, unsigned char> string_to_ip_and_mask(const std::string& str);
sockaddr_in make_broadcast_address(unsigned host_ip, unsigned char mask);
sockaddr_in make_network_address(unsigned host_ip, unsigned char mask);
sockaddr_in make_my_address(unsigned host_ip);
std::string address_to_string(const sockaddr_in& addr);
bool belongs_to_subnet(const sockaddr_in& subnet_addr, const sockaddr_in& foreign_addr, unsigned char mask);
}
