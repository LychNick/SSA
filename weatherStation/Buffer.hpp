#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <deque>
#include "Request.hpp"

class Buffer
{
public:
  Buffer(int size);
  bool isFull();
  bool isEmpty();
  void pushRequest(request_t request);
  request_t popOldest();
  request_t popLast();
  int getSize();
private:
  int size_;
  std::deque<request_t> queue_;
};

#endif // !BUFFER_HPP

