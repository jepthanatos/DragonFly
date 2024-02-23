#include <gtest/gtest.h>

#include "WorldManager.h"
#include "Object.h"

using namespace df;

TEST(TestWorldManager, startUp)
{
    EXPECT_EQ(0, WM.startUp());
    EXPECT_EQ(true, WM.isStarted());
}

TEST(TestWorldManager, shutDown)
{
    WM.shutDown();
    EXPECT_EQ(false, WM.isStarted());
}

TEST(TestWorldManager, insertObject)
{
    WM.startUp();
    Object o;
    // EXPECT_EQ(0, WM.insertObject(&o));
    EXPECT_EQ(1, WM.getAllObjects().getCount());
    EXPECT_EQ(0, WM.removeObject(&o));
    EXPECT_EQ(0, WM.getAllObjects().getCount());
}

TEST(TestWorldManager, removeObject)
{
    Object o;
    EXPECT_EQ(0, WM.removeObject(&o));
    EXPECT_EQ(0, WM.getAllObjects().getCount());
}

TEST(TestWorldManager, objectsOfType)
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
