//============================================================================
// Name        : ObjectListIterator.h
// Author      : Jorge
// Copyright   : https://creativecommons.org/licenses/by/4.0/
// Description : Class to iterate over a object list.
//============================================================================

#include "ObjectListIterator.h"

//==============================================================================
/* ObjectListIterator */
//==============================================================================

namespace df
{
    ObjectListIterator::ObjectListIterator(const ObjectList *p_l)
    {
        m_p_list = p_l;
        first();
    }

    void ObjectListIterator::first()
    {
        m_index = 0;
    }

    void ObjectListIterator::next()
    {
        if (m_index < m_p_list->getCount())
            m_index++;
    }

    bool ObjectListIterator::isDone() const
    {
        return (m_index == m_p_list->getCount());
    }

    Object *ObjectListIterator::currentObject() const
    {
        return m_p_list->m_objects[m_index];
    }
}
