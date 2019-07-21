#pragma once

#include <string>
#include <local_network.hpp>
#include <remote_network.hpp>
#include <vector>

class router
{
    const int sockfd_;
    unsigned current_round_;
    std::vector<local_network> local_networks_;
    remote_network remote_networks_;

  public:

    router();
    void add_local_network(const std::string& ip_mask, unsigned distance);
    void listen(unsigned seconds);
    void broadcast();
    void print();
};