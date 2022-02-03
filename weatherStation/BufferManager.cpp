#include "BufferManager.hpp"

BufferManager::BufferManager(Buffer& buffer, StatisticManager& statistic) :
  buffer_(buffer), 
  statistic_(statistic)
{
  statistic_.pushBuffer(buffer.getSize());
}

bool BufferManager::pushRequest(request_t request)
{
  if (!buffer_.isFull()) 
  {
    buffer_.pushRequest(request);
    statistic_.requestPushedInBuffer(request, request.incomeTime_);
    return true;
  }
  else 
  {
    request_t oldest = buffer_.popOldest();
    statistic_.denyRequest(oldest, request.incomeTime_);
    buffer_.pushRequest(request);
    statistic_.requestPushedInBuffer(request, request.incomeTime_);
    return false;
  }
}
