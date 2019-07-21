#pragma once

#include <string>
#include <chunk_pool.hpp>
#include <netinet/in.h>

class transport
{
    const int sockfd_;
    sockaddr_in host_address_;
    chunk_pool cp_;

    void receive();
    void request();

  public:

    transport(const std::string& ip, unsigned short port, const std::string& out_filename, unsigned requested_size);
    void run();
};
