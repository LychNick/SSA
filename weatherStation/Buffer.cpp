#include "Buffer.hpp"

Buffer::Buffer(int size)
{
  size_ = size;
}

bool Buffer::isFull()
{
  return queue_.size() >= size_;
}

bool Buffer::isEmpty()
{
  return queue_.size() == 0;
}

void Buffer::pushRequest(request_t request)
{
  queue_.push_back(request);
}

request_t Buffer::popOldest()
{
  request_t oldestRequest = queue_.front();
  queue_.pop_front();
  return oldestRequest;
}

request_t Buffer::popLast()
{
  request_t lastRequest = queue_.back();
  queue_.pop_back();
  return lastRequest;
}

int Buffer::getSize()
{
  return size_;
}
