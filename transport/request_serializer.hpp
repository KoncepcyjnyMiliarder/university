#pragma once

#include <string>

namespace request_serializer
{
std::string make_request_string(unsigned begin, unsigned end);
bool dissect_response(const char* recvbuf, unsigned recvsize, unsigned* chunk_begin, unsigned* chunk_size, const char** data);
}