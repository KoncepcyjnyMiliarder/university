#pragma once

#include <unordered_map>

struct remote_network
{
  struct endpoint
  {
    unsigned char mask;
    unsigned accessible_by_ip;
    long last_reply_round;
    unsigned distance;
  };

  std::unordered_map<unsigned, endpoint> ip_to_endpoint;
};