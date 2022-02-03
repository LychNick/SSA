#include "StatisticManager.hpp"

StatisticManager::StatisticManager(std::ostream& out, bool isAuto, int sources) :
  out_(out),
  sources_(sources),
  isAuto_(isAuto)
{
  for (int i = 0; i < sources; i++) 
  {
    sourcesCount_.push_back(0);
    sourcesGood_.push_back(0);
  }
}

void StatisticManager::pushDevice()
{
  deviceState_.push_back(false);
}

void StatisticManager::pushBuffer(int size)
{
  for (int i = 0; i < size; i++)
  {
    bufferState_.push_back(false);
  }
}

void StatisticManager::deviceDoneWorkWith(int device, request_t& request, double time)
{
  if (time > fullTime_)
  {
    fullTime_ = time;
  }

  deviceState_[device] = false;
  requests_[request.number_].residenceTime_ = time - requests_[request.number_].incomeTime_;
  if (!isAuto_)
  {
    out_ << "Device: " << device << " done with request " << request.number_
      << " at " << time << "\n\n";
  }
  printState();
}


void StatisticManager::generateRequest(request_t& request, double time)
{
  if (time > fullTime_)
  {
    fullTime_ = time;
  }
  requests_.push_back(request);
  if (!isAuto_)
  {
    out_ << "request: " << request.number_ << " time: " << time << '\n';
  }
}
static int ptr = 0;
void StatisticManager::requestPushedInBuffer(request_t& request, double time)
{
  if (time > fullTime_)
  {
    fullTime_ = time;
  }
  bufferState_[ptr++] = true;
  if (!isAuto_)
  {
    out_ << "request: " << request.number_ << " put in buffer" << "\n\n";
  }
  printState();
}

void StatisticManager::denyRequest(request_t& request, double time)
{
  if (time > fullTime_)
  {
    fullTime_ = time;
  }
  ptr--;
  bufferState_[0] = 2;
  requests_[request.number_].isGood_ = false;
  if (!isAuto_)
  {
    out_ << "!request : " << request.number_ << " denied at " << time << '\n';
  }
}

void StatisticManager::deviceStartWorkWith(int device, request_t& request, double time)
{
  if (time > fullTime_)
  {
    fullTime_ = time;
  }
  bufferState_[--ptr] = false;
  deviceState_[device] = true;
  requests_[request.number_].waitingTime_ = time - requests_[request.number_].incomeTime_;
  if (!isAuto_)
  {
    out_ << "Device: " << device << " start work with "
      << request.number_ << " request at " << time << "\n\n";
  }
  printState();
}

void StatisticManager::pushDevicesTime(std::vector<double> devTime)
{
  devicesTime_ = devTime;
}

void StatisticManager::printState()
{
  if (!isAuto_) 
  {
    out_ << "Buffer state:\n";
    for (int i = 0; i < bufferState_.size(); i++)
    {
      out_ << i << ' ';
    }
    out_ << '\n';
    for (int i = 0; i < bufferState_.size(); i++)
    {
      if (i != 0)
      {
        out_.width(2);
      }
      if (bufferState_[i] == 0)
      {
        out_ << ' ';
      }
      if (bufferState_[i] == 1)
      {

        out_ << '*';
      }
      if (bufferState_[i] == 2)
      {
        out_ << 'X';
        bufferState_[0] = 1;
      }
    }
    out_ << '\n';
    out_ << "Devices state:\n";
    for (int i = 0; i < deviceState_.size(); i++) 
    {
      out_ << i << ' ';
    }
    out_ << '\n';
    for (int i = 0; i < deviceState_.size(); i++)
    {
      if (i != 0)
      {
        out_.width(2);
      }
      if (deviceState_[i]) 
      {
        
        out_ << '*';
      }
      else 
      {
        out_ << ' ';
      }
    }
    std::cin.get();
  }
}

void StatisticManager::generateStatistic()
{
  double denyP = 0;
  double fulResidenceTime = 0;
  double fulWaitingTime = 0;
  double goodReqCount = 0;
  for (int i = 0; i < requests_.size(); i++) 
  {
    denyP += 1. - requests_[i].isGood_;
    if (requests_[i].isGood_) 
    {
      fulResidenceTime += requests_[i].residenceTime_;
      fulWaitingTime += requests_[i].waitingTime_;
      goodReqCount++;
    }
    else 
    {
    }
  }
  denyP /= requests_.size();
  //среднее время
  out_ << "avg residence time : " << fulResidenceTime / goodReqCount << "\n";
  out_ << "avg waiting time : " << fulWaitingTime / goodReqCount << "\n";
  //дисперсия
  double dispRes = 0;
  double dispWait = 0;
  
  for (int i = 0; i < requests_.size(); i++)
  {
    sourcesCount_[requests_[i].source_]++;
    if (requests_[i].isGood_)
    {
      sourcesGood_[requests_[i].source_]++;
      dispRes += std::pow((requests_[i].residenceTime_ - fulResidenceTime / goodReqCount) , 2);
      dispWait += std::pow((requests_[i].waitingTime_ - fulWaitingTime / goodReqCount) , 2);
    }
  }
  for (int i = 0; i < sources_; i++)
  {
    out_ << "Source " << i << '\n';
    out_ << "\tcount of requests : " << sourcesCount_[i] 
      << "\n\tprobability of failure : "
      << (sourcesCount_[i] - sourcesGood_[i])/ sourcesCount_[i] * 100 << '\n';
  }
  out_ << "\ndisp residence time : " << dispRes / (goodReqCount - 1) << "\n";
  out_ << "disp waiting time : " << dispWait / (goodReqCount - 1) << "\n";
  //вероятность отказа
  out_ << "probability of failure : " << denyP * 100 << "%\n";
  out_ << "full time : " << fullTime_ << "\n";
  double avgWorkLoad = 0;
  for (int i = 0; i < devicesTime_.size(); i++)
  {
    double workLoad = devicesTime_[i] / fullTime_;
    avgWorkLoad += workLoad;
    out_ << "device " << i << " workload is " << workLoad * 100 << "%\n";
  }
  avgWorkLoad = avgWorkLoad / devicesTime_.size();
  out_ << "avg device workLoad : " << avgWorkLoad * 100 << "%\n";

}
