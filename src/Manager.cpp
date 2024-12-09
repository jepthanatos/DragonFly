#include "Manager.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"

namespace df
{
    void Manager::setType(std::string new_type)
    {
        m_type = new_type;
    }

    Manager::Manager() : m_type{"None"}, m_is_started{false} {}

    Manager::~Manager() {}

    std::string Manager::getType() const
    {
        return m_type;
    }

    int Manager::startUp()
    {
        m_is_started = true;
        return EXIT_SUCCESS;
    }

    void Manager::shutDown()
    {
        m_is_started = false;
    }

    bool Manager::isStarted() const
    {
        return m_is_started;
    }

    int Manager::onEvent(const Event *p_event) const
    {
        int count = 0;

        ObjectList worldObjects = WM.getAllObjects();
        ObjectListIterator li(&worldObjects);
        for (li.first(); !li.isDone(); li.next())
        {
            li.currentObject()->eventHandler(p_event);
        }

        return EXIT_SUCCESS;
    }

}