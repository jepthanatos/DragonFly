#include <gtest/gtest.h>

#include "WorldManager.h"
#include "ObjectListIterator.h"

using namespace df;

TEST(TestWorldManagerSpecial, startUp)
{
    EXPECT_EQ(0, WM.startUp());
    EXPECT_EQ(true, WM.isStarted());
}

TEST(TestWorldManagerSpecial, shutDown)
{
    WM.shutDown();
    EXPECT_EQ(false, WM.isStarted());
}

class TestWorldManager : public ::testing::Test
{
    void SetUp() override
    {
        WM.startUp();
    }

    virtual void TearDown()
    {
        WM.shutDown();
    }
};

TEST_F(TestWorldManager, insertObject)
{
    Object *o = new Object{};
    EXPECT_EQ(1, WM.getAllObjects().getCount());
    EXPECT_EQ(0, WM.removeObject(o));
    EXPECT_EQ(0, WM.getAllObjects().getCount());
}

TEST_F(TestWorldManager, removeObject)
{
    Object o;
    EXPECT_EQ(0, WM.removeObject(&o));
    EXPECT_EQ(0, WM.getAllObjects().getCount());
}

TEST_F(TestWorldManager, objectsOfType)
{
    Object o;
    std::string type = "df::test";
    o.setType(type);
    // WM.insertObject(&o);
    ObjectList ol = WM.objectsOfType(type);
    EXPECT_EQ(1, ol.getCount());
    ObjectListIterator li(&ol);
    for (li.first(); not li.isDone(); li.next())
    {
        EXPECT_EQ(type, li.currentObject()->getType());
    }
}

TEST_F(TestWorldManager, moveObjectHardOnHardNotPossible)
{
    Object *o1 = new Object{};
    Object *o2 = new Object{};
    o1->setSolidness(HARD);
    o2->setSolidness(HARD);
    Vector v1(1, 1);
    Vector v2(2, 2);
    o1->setPosition(v1);
    o2->setPosition(v2);

    EXPECT_TRUE(WM.moveObject(o1, v2) == EXIT_FAILURE);
}

TEST_F(TestWorldManager, moveObjectHardOnSoftIsNotPossible)
{
    Object *o1 = new Object{};
    Object *o2 = new Object{};
    o1->setSolidness(HARD);
    o2->setSolidness(SOFT);
    Vector v1(1, 1);
    Vector v2(2, 2);
    o1->setPosition(v1);
    o2->setPosition(v2);

    EXPECT_TRUE(WM.moveObject(o1, v2) == EXIT_FAILURE);
}

TEST_F(TestWorldManager, moveObjectHardOnSoftIsPossible)
{
    Object *o1 = new Object{};
    Object *o2 = new Object{};
    o1->setSolidness(HARD);
    o2->setSolidness(SOFT);
    Vector v1(1, 1);
    Vector v2(2, 2);
    o1->setPosition(v1);
    o2->setPosition(v2);
    o1->setNoSoft(false);

    EXPECT_TRUE(WM.moveObject(o1, v2) == EXIT_SUCCESS);
}