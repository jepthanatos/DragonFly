//
// EventStep - A "step" event, generated once per game loop.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

#include "Event.h"

namespace df
{

  const std::string STEP_EVENT = "df::step";

  class EventStep : public Event
  {

  private:
    int m_step_count; // Iteration number of game loop.

  public:
    // Default constructor.
    EventStep();

    // Constructor with initial step count.
    EventStep(int init_step_count);

    // Set step count.
    void setStepCount(int new_step_count);

    // Get step count.
    int getStepCount() const;
  };

} // end of namespace df
#endif // __EVENT_STEP_H__
