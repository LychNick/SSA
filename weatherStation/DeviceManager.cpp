#include "DeviceManager.hpp"

DeviceManager::DeviceManager(Buffer& buffer, StatisticManager& statistic) :
  buffer_(buffer),
  statistic_(statistic)
{
}

void DeviceManager::createDevice(double speed)
{
  Device newDevice(speed);
  devices_.push_back(newDevice);
  statistic_.pushDevice();
}

int DeviceManager::selectDevice()
{
  for (int i = 0; i < devices_.size(); i++) 
  {
    if (!devices_[i].isWorking()) 
    {
      return i;
    }
  }
}

bool DeviceManager::isFreeDevice()
{
  for (int i = 0; i < devices_.size(); i++) 
  {
    if (!devices_[i].isWorking()) 
    {
      return true;
    }
  }
  return false;
}

bool DeviceManager::isAllDevicesFree()
{
  for (int i = 0; i < devices_.size(); i++)
  {
    if (devices_[i].isWorking())
    {
      return false;
    }
  }
  return true;
}

request_t DeviceManager::selectRequest()
{
  return buffer_.popLast();
}

double DeviceManager::nearEventTime()
{
  double time = INT_MAX;
  for (int i = 0; i < devices_.size(); i++)
  {
    if (devices_[i].isWorking())
    {
      if (devices_[i].getDoneTime() < time) 
      {
        time = devices_[i].getDoneTime();
      }
    }
  }
  return time;
}

void DeviceManager::work(double time)
{
  for (int i = 0; i < devices_.size(); i++)
  {
    if (devices_[i].isWorking())
    {
      if (devices_[i].getDoneTime() <= time)
      {
        request_t request = devices_[i].popRequest();
        statistic_.deviceDoneWorkWith(i, request, time);
      }
    }
  }
  if ((isFreeDevice()) && (!buffer_.isEmpty())) 
  {
    int deviceNumber = selectDevice();
    request_t request = selectRequest();
    devices_[deviceNumber].pushRequest(request, time);
    statistic_.deviceStartWorkWith(deviceNumber, request, time);
  }
}


int DeviceManager::getDevicesCount()
{
  return devices_.size();
}

std::vector<double> DeviceManager::getDeviceFullTime()
{
  std::vector<double> devTime;
  for (int i = 0; i < devices_.size(); i++) 
  {
    devTime.push_back(devices_[i].getFullWorkTime());
  }
  return devTime;
}