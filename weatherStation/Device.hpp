#ifndef DEVICE_HPP
#define DEVICE_HPP
#include "Request.hpp"

class Device
{
public:
  Device(double time);
  bool isWorking();
  request_t popRequest();
  void pushRequest(request_t request, double time);
  double getDoneTime();
  double getFullWorkTime();
private:
  bool isWorking_ = false;
  double workTime_ = 0;
  double fullWorkTime_ = 0;
  double workDoneTime_ = 0;
  request_t request_;
};

#endif // !DEVICE_HPP

