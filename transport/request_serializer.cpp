/*
Krzysztof Pyrkosz
261282
*/
#include <request_serializer.hpp>
#include <cstdlib>

namespace request_serializer
{
std::string make_request_string(unsigned begin, unsigned end)
{
  return std::string("GET ") + std::to_string(begin) + ' ' + std::to_string(end) + '\n';
}

bool dissect_response(const char* recvbuf, unsigned recvsize, unsigned* chunk_begin, unsigned* chunk_size, const char** data)
{
  const char* curr_ptr = recvbuf + 5; //skip "DATA "
  char* strtoul_end;
  *chunk_begin = std::strtoul(curr_ptr, &strtoul_end, 10);
  curr_ptr = strtoul_end;
  *chunk_size = std::strtoul(curr_ptr, &strtoul_end, 10);
  curr_ptr = strtoul_end;
  while (*curr_ptr++ != '\n');
  *data = curr_ptr;
  return recvbuf + recvsize >= curr_ptr + *chunk_size;
}

}
