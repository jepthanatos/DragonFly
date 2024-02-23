#include <gtest/gtest.h>

#include "Skill.h"

using namespace df;

TEST(TestSkill, delta)
{
    Skill<SkillType::SWORD> s{1, 1, 1};

    ASSERT_EQ(s.getType(), SkillType::SWORD);
}