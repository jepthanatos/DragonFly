#include <gtest/gtest.h>

#include "ObjectList.h"

using namespace df;

TEST(ObjectListTest, EmptyList)
{
    ObjectList ol;
    EXPECT_TRUE(ol.isEmpty());
    EXPECT_EQ(0, ol.getCount());
    EXPECT_FALSE(ol.isFull());
}

TEST(ObjectListTest, AddOneObject)
{
    ObjectList ol;
    Object o;
    ol.insert(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(1, ol.getCount());
    // Depends on MAX_COUNT_INIT const declared in ObjectList.h
    // If MAX_COUNT_INIT is not 1 then the list will not be full.
    EXPECT_TRUE(ol.isFull());
}

TEST(ObjectListTest, AddSeveralObjects)
{
    ObjectList ol;
    Object o;
    for (int i = 0; i < 10; i++)
    {
        ol.insert(&o);
    }
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(10, ol.getCount());
    EXPECT_FALSE(ol.isFull());
}

TEST(ObjectListTest, AddOneObjectThenRemove)
{
    ObjectList ol;
    Object o;
    ol.insert(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(1, ol.getCount());
    EXPECT_TRUE(ol.isFull());

    ol.remove(&o);
    EXPECT_TRUE(ol.isEmpty());
    EXPECT_EQ(0, ol.getCount());
    EXPECT_FALSE(ol.isFull());
}

TEST(ObjectListTest, AddSeveralObjectsThenRemove)
{
    ObjectList ol;
    Object o;
    for (int i = 0; i < 10; i++)
    {
        ol.insert(&o);
    }
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(10, ol.getCount());
    EXPECT_FALSE(ol.isFull());

    ol.remove(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(9, ol.getCount());
    EXPECT_FALSE(ol.isFull());
}

TEST(ObjectListTest, ClearAfterInsert)
{
    ObjectList ol;
    Object o;
    for (int i = 0; i < 10; i++)
    {
        ol.insert(&o);
    }
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(10, ol.getCount());
    EXPECT_FALSE(ol.isFull());

    ol.clear();
    EXPECT_TRUE(ol.isEmpty());
    EXPECT_EQ(0, ol.getCount());
    EXPECT_FALSE(ol.isFull());

    ol.insert(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(1, ol.getCount());
    EXPECT_FALSE(ol.isFull());
}

TEST(ObjectListTest, InsertClearInsert)
{
    ObjectList ol;
    Object o;
    ol.insert(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(1, ol.getCount());
    EXPECT_TRUE(ol.isFull());

    ol.clear();
    EXPECT_TRUE(ol.isEmpty());
    EXPECT_EQ(0, ol.getCount());
    EXPECT_FALSE(ol.isFull());

    ol.insert(&o);
    EXPECT_FALSE(ol.isEmpty());
    EXPECT_EQ(1, ol.getCount());
    EXPECT_TRUE(ol.isFull());
}
