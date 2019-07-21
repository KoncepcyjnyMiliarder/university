/*
Krzysztof Pyrkosz
261282
*/
#include <chunk_pool.hpp>
#include <sys/time.h>

long long current_timestamp()
{
  timeval tv;
  gettimeofday(&tv, nullptr);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

chunk_pool::chunk_pool(unsigned size, const std::string& out_filename)
  : filename_(out_filename),
    begin_(0),
    fileout_(out_filename)
{
  if (size == 0)
    throw std::runtime_error("file size has to be nonzero");
  if(!fileout_)
    throw std::runtime_error("unable to open outfile");
  for (unsigned i = 0; i < size - 999; i += 1000)
    begin_to_chunk_.emplace(i, chunk(1000));
  if(size % 1000)
    begin_to_chunk_.emplace(size - (size % 1000), chunk(size % 1000));
  total_chunks_ = begin_to_chunk_.size();
}

std::pair<unsigned, unsigned> chunk_pool::get_wanted_chunk_and_size()
{
  if (begin_to_chunk_.empty())
    return { 0, 0 };
  auto best_candidate = begin_to_chunk_.begin();
  int attempts = 0;
  for (auto it = begin_to_chunk_.begin(); it != begin_to_chunk_.end(); ++it)
  {
    if (++attempts > 1000)
     return { 0, 0 }; 
    if (it->second.was_received)
      continue;
    if (it->second.last_request_time + 300 < current_timestamp())
    {
      it->second.last_request_time = current_timestamp();
      best_candidate = it;
      break;
    }
  }
  return std::pair<unsigned, unsigned>(best_candidate->first, best_candidate->second.expected_size);
}

bool chunk_pool::is_finished()
{
  return begin_to_chunk_.empty();
}

void chunk_pool::on_chunk_received(unsigned begin, unsigned size, const char* data)
{
  if (begin < begin_ )
    return;
  if (begin_to_chunk_.count(begin) == 0)
    return;
  if (begin_to_chunk_.at(begin).was_received)
    return;
  auto& my_node = begin_to_chunk_.at(begin);
  my_node.was_received = true;
  my_node.data = std::string(data, size);
  while(!begin_to_chunk_.empty() && begin_to_chunk_.begin()->second.was_received)
  {
    auto& begin_node = begin_to_chunk_.at(begin_);
    fileout_.write(begin_node.data.data(), begin_node.data.size());
    begin_ += begin_node.data.size();
    begin_to_chunk_.erase(begin_to_chunk_.begin());
    printf("Received%*.2f%%\n", 20, 100.0f * ((float)(total_chunks_ - begin_to_chunk_.size())) / total_chunks_);
  }
}
