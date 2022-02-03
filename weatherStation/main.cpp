#include <iostream>
#include "BufferManager.hpp"
#include "Source.hpp"
#include "DeviceManager.hpp"
#include "Buffer.hpp"
#include "StatisticManager.hpp"

//1.	Поступление заявки в СМО(момент генерации заявки источником);
//2.	Освобождение прибора(готовность прибора взять заявку на обслуживание);
//3.	Окончание процесса моделирования, т.е.момент

//Tпреб - время пребывания заявки в системе
//TБП — среднее время ожидания заявки.
//Дисперсии Tобсл  и TБП ;
//Коэффициенты  использования  приборов  (суммарное  время занятости каждого прибора / общее время реализации).

//11.		ИБ	И31	П32	Д1033	Д10О3	Д2П1	Д2Б2	ОР1	ОД2
/*
Источники:
ИБ – бесконечный
И31 - пуассоновский	для	бесконечных

Приборы :
П32 – равномерный закон распределения 
времени обслуживания;

Описание дисциплин постановки и выбора :
Дисциплина буферизации :
Д1033 – Постановка на свободное
Дисциплина отказа :
Д10О3 – Старая в буфере;

Дисциплина постановки на обслуживание :
Выбор прибора :
Д2П1 – Приоритет по номеру прибора;
Выбор заявки из буфера :
Д2Б2 – LIFO
*/

const int N = 1000;
double lyamda = 2;
const double sourceCount = 5;
const int bufferSize = 10;
const int deviceCount = 4;
const double deviceTime = 1;


int main()
{
  StatisticManager statistic(std::cout, true, sourceCount);
  srand(time(0));
  double globalTime = 0;
  int sourcePtr = 0;
  request_t request;
  Buffer buffer(bufferSize);
  BufferManager bufferManager(buffer, statistic);
  DeviceManager deviceManager(buffer, statistic);
  for (int i = 0; i < deviceCount; i++) 
  {
    deviceManager.createDevice(deviceTime);
  }
  for (int i = 0; i < N; i++)
  {
    globalTime += Source::genereteRequest(lyamda * sourceCount);
    request.incomeTime_ = globalTime;
    request.source_ = sourcePtr;
    if (deviceManager.nearEventTime() < request.incomeTime_)
    {
      deviceManager.work(deviceManager.nearEventTime());
    }
    statistic.generateRequest(request, request.incomeTime_);
    bufferManager.pushRequest(request);
    deviceManager.work(request.incomeTime_);
    request.number_++;
    if (sourcePtr < sourceCount - 1)
    {
      sourcePtr++;
    }
    else 
    {
      sourcePtr = 0;
    }
  }
  while ((!buffer.isEmpty()) || (!deviceManager.isAllDevicesFree())) 
  {
    deviceManager.work(deviceManager.nearEventTime());
  }
  statistic.pushDevicesTime(deviceManager.getDeviceFullTime());
  statistic.generateStatistic();
}
