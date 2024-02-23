#include <gtest/gtest.h>

#include "Event.h"

using namespace df;

TEST(TestEvent, setType)
{
    Event e;
    EXPECT_EQ("df::undefined", e.getType());
    e.setType("df::other");
    EXPECT_EQ("df::other", e.getType());
}