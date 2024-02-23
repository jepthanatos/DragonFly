#ifndef __CLOCK_H__
#define __CLOCK_H__

// System includes.
#include <string>
#include <chrono>

namespace df
{

  class Clock
  {

  private:
    // Previous time delta() called (in microsec).
    std::chrono::time_point<std::chrono::steady_clock> previous_time;

  public:
    // Sets previous time to current time.
    Clock();

    // Return time elapsed since delta() vas last called, -1 if error.
    // Resets previous time.
    // Units are miliseconds.
    std::chrono::milliseconds delta();

    // Return time elapsed since delta() las last called, -1 if error.
    // Does not reset previous time.
    // Units are miliseconds.
    std::chrono::milliseconds split() const;
  };

} // end of namespace df
#endif // __CLOCK_H__
