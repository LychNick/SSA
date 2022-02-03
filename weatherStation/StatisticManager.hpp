#ifndef STATISTIC_MANAGER_HPP
#define STATISTIC_MANAGER_HPP
#include <iostream>
#include <vector>
#include <deque>

#include "Request.hpp"

class StatisticManager
{
public:
  StatisticManager(std::ostream& out, bool isAuto, int sources);
  void deviceStartWorkWith(int device, request_t& request, double time);
  void deviceDoneWorkWith(int device, request_t& request, double time);
  void requestPushedInBuffer(request_t& request, double time);
  void generateRequest(request_t& request, double time);
  void denyRequest(request_t& request, double time);
  void pushDevicesTime(std::vector<double> devTime);
  void pushDevice();
  void pushBuffer(int size);
  void generateStatistic();
  void printState();

private:
  double fullTime_ = 0;
  bool isAuto_;
  std::deque<int> bufferState_;
  std::vector<bool> deviceState_;
  int sources_ = 0;
  std::vector<double> sourcesCount_;
  std::vector<double> sourcesGood_;

  std::vector<request_t> requests_;
  std::vector<double> devicesTime_;
  std::ostream& out_;
};

#endif // !STATISTIC_MANAGER_HPP

