/*
Krzysztof Pyrkosz
261282
*/#include <iostream>
#include <request_serializer.hpp>
#include <transport.hpp>

int main(int argc, char** argv)
{
  if (argc != 5)
  {
    printf("Usage %s host_ip port output_file bytecount\n", argv[0]);
    return 1;
  }
  try
  {
    transport(argv[1], (unsigned short)std::stoul(argv[2]), argv[3], std::stoul(argv[4])).run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  return 0;
}
