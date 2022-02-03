#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP
#include <vector>
#include <iostream>
#include "Device.hpp"
#include "Buffer.hpp"
#include "Request.hpp"

#include "StatisticManager.hpp"

class DeviceManager
{
public:
  DeviceManager(Buffer& buffer, StatisticManager& statistic);
  void createDevice(double speed);
  int selectDevice();
  bool isFreeDevice();
  bool isAllDevicesFree();
  request_t selectRequest();
  double nearEventTime();
  void work(double time);
  int getDevicesCount();
  std::vector<double> getDeviceFullTime();
private:
  Buffer& buffer_;
  StatisticManager& statistic_;
  std::vector<Device> devices_;
};

#endif // !DEVICE_MANAGER_HPP
