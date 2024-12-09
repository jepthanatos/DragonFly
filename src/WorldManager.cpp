#include "WorldManager.h"
#include "LogManager.h"
#include "Utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ObjectListIterator.h"

namespace df
{
    int WorldManager::startUp()
    {
        Manager::setType("WorldManager");
        LM.getLogger()->debug("WorldManager::startUp");
        m_updates.clear();
        m_deletions.clear();
        return Manager::startUp();
    }

    void WorldManager::shutDown()
    {
        auto deleteObjects = [](ObjectList &ol)
        {
            ObjectListIterator li(&ol);
            for (li.first(); !li.isDone(); li.next())
                delete li.currentObject();
        };

        ObjectList ol1(m_updates);
        deleteObjects(ol1);

        ObjectList ol2(m_deletions);
        deleteObjects(ol2);

        Manager::shutDown();
        LM.getLogger()->debug("WorldManager::shutDown");
    }

    int WorldManager::insertObject(Object *p_o)
    {
        return m_updates.insert(p_o);
    }

    int WorldManager::removeObject(Object *p_o)
    {
        ObjectListIterator li(&m_deletions);
        for (li.first(); !li.isDone(); li.next())
        {
            if (li.currentObject() == p_o)
                return EXIT_SUCCESS;
        }
        return m_updates.remove(p_o);
    }

    ObjectList WorldManager::getAllObjects() const
    {
        return m_updates;
    }

    ObjectList WorldManager::objectsOfType(std::string type) const
    {
        ObjectList ol;
        ObjectListIterator li(&m_updates);
        for (li.first(); !li.isDone(); li.next())
        {
            if (li.currentObject()->getType() == type)
            {
                ol.insert(li.currentObject());
            }
        }
        return ol;
    }

    int WorldManager::markForDelete(Object *p_o)
    {
        ObjectListIterator li(&m_deletions);
        for (li.first(); !li.isDone(); li.next())
            if (li.currentObject() == p_o)
                return EXIT_SUCCESS;

        return m_deletions.insert(p_o);
    }

    void WorldManager::update()
    {
        ObjectListIterator li(&m_updates);
        for (li.first(); !li.isDone(); li.next())
        {
            Vector new_pos = li.currentObject()->predictPosition();
            if (new_pos != li.currentObject()->getPosition())
                moveObject(li.currentObject(), new_pos);
        }

        // LM.getLogger()->debug("WorldManager::update");
        ObjectListIterator li_deletions(&m_deletions);
        for (li_deletions.first(); !li_deletions.isDone(); li_deletions.next())
            delete li_deletions.currentObject();

        m_deletions.clear();
    }

    void WorldManager::draw()
    {
        // TODO: Optimize this please.
        ObjectListIterator li(&m_updates);
        for (int alt = 0; alt < MAX_ALTITUDE; ++alt)
            for (li.first(); !li.isDone(); li.next())
                if (li.currentObject()->getAltitude() == alt)
                    li.currentObject()->draw();
    }

    int WorldManager::moveObject(Object *p_o, Vector where)
    {
        if (p_o->isSolid())
        {
            ObjectList list = getCollisions(p_o, where);

            if (not list.isEmpty())
            {
                bool do_move = true; // Assume can move.

                ObjectListIterator li(&list);
                for (li.first(); !li.isDone(); li.next())
                {
                    Object *p_temp_o = li.currentObject();

                    // Create collision event.
                    EventCollision c(p_o, p_temp_o, where);

                    // Send to both objects.
                    p_o->eventHandler(&c);
                    p_temp_o->eventHandler(&c);

                    // If both HARD, then cannot move.
                    if (p_o->getSolidness() == HARD and p_temp_o->getSolidness() == HARD)
                        do_move = false;

                    // If object does not want to move on to soft objects, don't move.
                    if (p_o->getNoSoft() and p_temp_o->getSolidness() == SOFT)
                        do_move = false;
                }

                if (!do_move)
                    return EXIT_FAILURE; // Move not allowed.
            }
        }

        // If here, no collision between two HARD objects so allow move.
        p_o->setPosition(where);

        // Generate out of bounds event and send to Object.
        EventOut ov;
        p_o->eventHandler(&ov);

        return EXIT_SUCCESS; // Move was ok.
    }

    ObjectList WorldManager::getCollisions(const Object *p_o, Vector where) const
    {
        ObjectList collision_list;

        ObjectListIterator li(&m_updates);

        for (li.first(); !li.isDone(); li.next())
        {

            Object *p_temp_o = li.currentObject();

            if (p_temp_o != p_o)
            {
                if (positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid())
                    collision_list.insert(p_temp_o);
            }
        }

        return collision_list;
    }
}