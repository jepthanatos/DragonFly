#include <gtest/gtest.h>

#include "LogManager.h"

using namespace df;

TEST(TestLogManager, startUp)
{
    EXPECT_EQ(0, LM.startUp());
    EXPECT_EQ(true, LM.isStarted());
}

TEST(TestLogManager, shutDown)
{
    LM.shutDown();
    EXPECT_EQ(false, LM.isStarted());
}
