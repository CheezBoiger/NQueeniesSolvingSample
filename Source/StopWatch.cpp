// Copyright (c) 2017 Mario Garcia, MIT License.
#include "StopWatch.hpp"

#include <chrono>


namespace nq {


std::chrono::time_point<std::chrono::high_resolution_clock> start;


void StopWatch::Start()
{
  start = std::chrono::high_resolution_clock::now();
}


real32 StopWatch::Stop()
{
  auto end = std::chrono::high_resolution_clock::now();
  long long t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  return t / 1000000.0f;
}
} // nq