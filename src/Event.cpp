#include "Event.h"

namespace df
{

    Event::Event() : m_event_type{UNDEFINED_EVENT}
    {
    }

    Event::~Event()
    {
    }

    void Event::setType(std::string new_type)
    {
        m_event_type = new_type;
    }

    std::string Event::getType() const
    {
        return m_event_type;
    }

} // end of namespace df
