#include <gtest/gtest.h>

#include "RankManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace df;

class TestRankManager : public ::testing::Test
{
    Skill<SkillType::SWORD> s{1, 1, 1};
};

TEST_F(TestRankManager, startUp)
{
    EXPECT_EQ(0, RM_SWORD.startUp());
    EXPECT_EQ(true, RM_SWORD.isStarted());
}

TEST_F(TestRankManager, shutDown)
{
    RM_SWORD.shutDown();
    EXPECT_EQ(false, RM_SWORD.isStarted());
}

TEST_F(TestRankManager, addPlayer)
{
    RM_SWORD.startUp();
    Player player{
        {"Test"},
        SkillType::SWORD,
        20};
    RM_SWORD.addPlayer(player);
    std::vector<Player> ranking{RM_SWORD.getRanking()};
    std::vector<Player> myRanking{std::move(player)};
    ASSERT_EQ(myRanking, ranking);
    RM_SWORD.shutDown();
}

TEST_F(TestRankManager, add100Players)
{
    RM_SWORD.startUp();
    srand(time(NULL));
    for (int i = 0; i < 100; ++i)
    {
        Player player{
            fmt::format("Player{}", i),
            SkillType::SWORD,
            rand() % 100};
        RM_SWORD.addPlayer(player);
    }
    RM_SWORD.printRanking();
    RM_SWORD.shutDown();
}