#pragma once

#include <map>
#include <string>
#include <fstream>
#include <ctime>

class chunk_pool
{
    struct chunk
    {
      std::string data;
      unsigned expected_size;
      time_t last_request_time;
      bool was_received;
      chunk(unsigned size)
        : expected_size(size),
	  last_request_time(0),
          was_received(false)
      {
      }
    };

    const std::string filename_;
    std::map<unsigned, chunk> begin_to_chunk_;
    unsigned begin_;
    unsigned total_chunks_;
    std::ofstream fileout_;

  public:

    chunk_pool(unsigned size, const std::string& out_filename);
    std::pair<unsigned, unsigned> get_wanted_chunk_and_size();
    bool is_finished();
    void on_chunk_received(unsigned begin, unsigned size, const char* data);
};
