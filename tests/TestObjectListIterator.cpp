#include <gtest/gtest.h>

#include "ObjectListIterator.h"

using namespace df;

TEST(ObjectListIteratorTest, EmptyList)
{
    ObjectList ol;
    ObjectListIterator li(&ol);
    EXPECT_TRUE(li.isDone());
}

TEST(ObjectListIteratorTest, AddOneObject)
{
    ObjectList ol;
    ObjectListIterator li(&ol);
    Object o;
    ol.insert(&o);
    EXPECT_FALSE(li.isDone());
    li.next();
    EXPECT_TRUE(li.isDone());
}

TEST(ObjectListIteratorTest, AddSeveralObjects)
{
    ObjectList ol;
    ObjectListIterator li(&ol);
    Object o;
    for (int i = 0; i < 10; i++)
    {
        ol.insert(&o);
    }
    EXPECT_FALSE(li.isDone());
    for (int i = 0; i < 10; i++)
    {
        li.next();
    }
    EXPECT_TRUE(li.isDone());
}

TEST(ObjectListIteratorTest, AddOneObjectThenRemove)
{
    ObjectList ol;
    ObjectListIterator li(&ol);
    Object o;
    ol.insert(&o);
    ol.remove(&o);
    EXPECT_TRUE(li.isDone());
}
