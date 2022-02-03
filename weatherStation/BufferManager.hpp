#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP
#include <iostream>

#include "Buffer.hpp"
#include "StatisticManager.hpp"

class BufferManager
{
public:
  BufferManager(Buffer& buffer, StatisticManager& statistic);
  bool pushRequest(request_t request);
private:

  StatisticManager& statistic_;
  Buffer& buffer_;
};

#endif // !BUFFER_MANAGER_HPP

