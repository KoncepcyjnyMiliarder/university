#pragma once

#include <unordered_map>
#include <string>
#include <netinet/in.h>

struct local_network
{
  const std::string str_representtion;
  const sockaddr_in broadcast_address;
  const sockaddr_in subnet_address;
  const sockaddr_in my_ip;
  const unsigned char mask;
  const unsigned distance;
  std::unordered_map<unsigned, unsigned> endpoint_to_last_reply;
};
