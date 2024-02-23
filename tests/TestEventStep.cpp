#include <gtest/gtest.h>

#include "EventStep.h"

using namespace df;

TEST(TestEventStep, constructor)
{
    EventStep e;
    EXPECT_EQ("df::step", e.getType());
    e.setType("df::other");
    EXPECT_EQ("df::other", e.getType());
}

TEST(TestEventStep, initStepCount)
{
    EventStep e(10);
    EXPECT_EQ(10, e.getStepCount());
}

TEST(TestEventStep, setStepCount)
{
    EventStep e;
    e.setStepCount(10);
    EXPECT_EQ(10, e.getStepCount());
}