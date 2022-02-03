#include "Device.hpp"
#include "Request.hpp"


Device::Device(double time) :
  workTime_(time),
  isWorking_(false)
{
}

bool Device::isWorking()
{
  return isWorking_;
}

request_t Device::popRequest()
{
  fullWorkTime_ += workTime_;
  isWorking_ = false;
  return request_;
}

void Device::pushRequest(request_t request, double time)
{
  request_ = request;
  workDoneTime_ = time + workTime_;
  isWorking_ = true;
}

double Device::getDoneTime()
{
  return workDoneTime_;
}

double Device::getFullWorkTime()
{
  return fullWorkTime_;
}
