#include <gtest/gtest.h>

#include "Object.h"
#include "Vector.h"

using namespace df;

TEST(TestObject, Constuctor)
{
    Object o;
    EXPECT_EQ(0, o.getId());
    EXPECT_STREQ("Object", o.getType().c_str());
}

TEST(TestObject, SetId)
{
    Object o;
    o.setId(999);
    EXPECT_EQ(999, o.getId());
}

TEST(TestObject, SetType)
{
    Object o;
    o.setType("Sword");
    EXPECT_EQ("Sword", o.getType());
}

TEST(TestObject, SetPosition)
{
    Object o;
    Vector v(1, 2);
    o.setPosition(v);
    Vector v1 = o.getPosition();
    EXPECT_EQ(1, v.getX());
    EXPECT_EQ(2, v.getY());
}

TEST(TestObject, CompleteTest)
{
    Object o1;
    Object o2;
    // REMEMBER: the cont is static you have to count the number of object
    // created in ALL test to get the id given to the object to be created.
    // EXPECT_EQ(4, o1.getId());
    // EXPECT_EQ(5, o2.getId());
    o1.setId(o2.getId());
    EXPECT_TRUE(o1.getId() == o2.getId());
    Vector v(1, 2);
    o1.setPosition(v);
    EXPECT_FALSE(o1.getPosition() == o2.getPosition());
}
