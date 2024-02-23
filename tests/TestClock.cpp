#include <gtest/gtest.h>

#include "Clock.h"

using namespace df;

TEST(TestClock, delta)
{
    Clock c;
    std::chrono::milliseconds delta = c.delta();
    EXPECT_NE(-1, std::chrono::duration_cast<std::chrono::milliseconds>(delta).count());
}

TEST(TestClock, split)
{
    Clock c;
    std::chrono::milliseconds split = c.split();
    EXPECT_NE(-1, std::chrono::duration_cast<std::chrono::milliseconds>(split).count());
}