#ifndef REQUEST_HPP
#define REQUEST_HPP

struct request_t
{
  int number_ = 0;
  int source_ = 0;
  double incomeTime_ = 0;
  double waitingTime_ = 0;
  double residenceTime_ = 0;
  bool isGood_ = true;
};

#endif // !REQUEST_HPP