// Engine includes.
#include "Clock.h"

namespace df
{

  Clock::Clock(void)
  {
    previous_time = std::chrono::steady_clock::now();
  }

  auto elapsedTime = [](auto previous_time, auto end)
  {
    auto aux1 = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
    auto aux2 = std::chrono::time_point_cast<std::chrono::milliseconds>(previous_time);
    std::chrono::milliseconds elapsed_time = aux1 - aux2;
    return elapsed_time;
  };

  std::chrono::milliseconds Clock::delta()
  {
    auto end = std::chrono::steady_clock::now();
    previous_time = end;
    return elapsedTime(previous_time, end);
  }

  std::chrono::milliseconds Clock::split() const
  {
    auto end = std::chrono::steady_clock::now();
    return elapsedTime(previous_time, end);
  }
} // end of namespace df