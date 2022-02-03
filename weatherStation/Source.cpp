#include "Source.hpp"

double Source::genereteRequest(double lyamda)
{
  return -1. / lyamda * std::log((double)((rand() % 99) + 1.) / 100.);
}
