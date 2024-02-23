//============================================================================
// Name        : ObjectList.cpp
// Author      : Jorge
// Copyright   : https://creativecommons.org/licenses/by/4.0/
// Description :
//============================================================================

#include "ObjectList.h"
#include "LogManager.h"

#include <string>
#include <sstream>

#include <stdio.h>
#include <string.h>

//==============================================================================
/* ObjectList */
//==============================================================================

namespace df
{
    /*------------------------------------------------------------------------------
     * Default constructor.
     */
    ObjectList::ObjectList()
    {
        LM.getLogger()->debug("ObjectList::Constructor");
        m_count = 0;
        max_count = MAX_COUNT_INIT;
        p_item = (Object **)malloc(sizeof(Object *) * max_count);
    }

    /*------------------------------------------------------------------------------
     * Destructor.
     */
    ObjectList::~ObjectList()
    {
        if (p_item != NULL)
        {
            free(p_item);
        }
        //LM.getLogger()->debug("ObjectList::Destructor");
    }

    /*------------------------------------------------------------------------------
     * Copy constructor.
     */
    ObjectList::ObjectList(const ObjectList &other)
    {
        p_item = (Object **)malloc(sizeof(Object *) * other.m_count);
        if (p_item != NULL)
        {
            if (memcpy(p_item, other.p_item, sizeof(Object *) * other.m_count) != NULL)
            {
                m_count = other.m_count;
                max_count = other.max_count;
            }
        }
    }

    /*------------------------------------------------------------------------------
     * Operator =
     */
    ObjectList &ObjectList::operator=(const ObjectList &rhs)
    {
        if (*this != rhs)
        {
            if (p_item != NULL)
            {
                free(p_item);
            }
            p_item = (Object **)malloc(sizeof(Object *) * rhs.m_count);
            if (p_item != NULL)
            {
                if (memcpy(p_item, rhs.p_item, sizeof(Object *) * rhs.m_count) != NULL)
                {
                    m_count = rhs.m_count;
                    max_count = rhs.max_count;
                }
            }
        }
        return *this;
    }

    /*------------------------------------------------------------------------------
     * Operator !=
     */
    bool ObjectList::operator!=(const ObjectList &other)
    {
        return !((*this->p_item) == *other.p_item);
    }

    /*------------------------------------------------------------------------------
     * Insert object pointer in list.
     * Return 0 if ok, else -1.
     * TODO: check if the object already exists in the list and modify the tests.
     */
    int ObjectList::insert(Object *object)
    {
        LM.getLogger()->debug("ObjectList::insert");
        // object->print();
        if (m_count == max_count)
        {
            LM.getLogger()->debug("ObjectList::insert - Making list bigger.");
            Object **tempObjects;
            tempObjects = (Object **)realloc(p_item, 2 * sizeof(Object *) * max_count);
            if (tempObjects != NULL)
            {
                p_item = tempObjects;
                max_count *= 2;
            }
            else
                return -1;
        }
        p_item[m_count] = object;
        m_count++;
        std::string msg = "ObjectList::insert - Number of elements in list: " + std::to_string(m_count);
        LM.getLogger()->debug(msg.c_str());
        return 0;
    }

    /*------------------------------------------------------------------------------
     * Remove object pointer from list.
     * Return 0 if found, else -1.
     * TODO: expect the m_count to be the half and realloc memory?
     */
    int ObjectList::remove(Object *object)
    {
        LM.getLogger()->debug("ObjectList::remove");
        for (int i = 0; i < m_count; i++)
        {
            if (p_item[i] == object)
            {
                // Pop last item from the end and swap over item to delete.
                p_item[i] = p_item[m_count - 1];
                m_count--;
                return 0; // Found.
            }
        }
        return -1; // Not found.
    }

    /*------------------------------------------------------------------------------
     * Clear list (setting m_count to 0).
     */
    void ObjectList::clear()
    {
        m_count = 0;
    }

    /*------------------------------------------------------------------------------
     * Return m_count of number of p_item in list.
     */
    int ObjectList::getCount() const
    {
        return m_count;
    }

    /*------------------------------------------------------------------------------
     * Return true if list is empty, else false.
     */
    bool ObjectList::isEmpty() const
    {
        return m_count == 0;
    }

    /*------------------------------------------------------------------------------
     * Return true if list is full, else false.
     */
    bool ObjectList::isFull() const
    {
        return m_count == max_count;
    }

    /*------------------------------------------------------------------------------
     * Add two lists, second appended to first.
     */
    ObjectList ObjectList::operator+(ObjectList list)
    {
        // Start with first list.
        ObjectList finalList = *this;

        // Iterate through second list, adding each element.
        ObjectListIterator listIter(&list);
        for (listIter.first(); !listIter.isDone(); listIter.next())
        {
            Object *pObject = listIter.currentObject();
            finalList.insert(pObject);
        }

        // Return combined list.
        return finalList;
    }
}
