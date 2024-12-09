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
        m_objects.reserve(MAX_COUNT_INIT);
        assert(m_objects.size() == 0);
    }

    /*------------------------------------------------------------------------------
     * Destructor.
     */
    ObjectList::~ObjectList()
    {
        // LM.getLogger()->debug("ObjectList::Destructor");
    }

    /*------------------------------------------------------------------------------
     * Copy constructor.
     */
    ObjectList::ObjectList(const ObjectList &other)
    {
        m_objects = other.m_objects;
    }

    /*------------------------------------------------------------------------------
     * Operator =
     */
    ObjectList &ObjectList::operator=(const ObjectList &rhs)
    {
        if (*this != rhs)
        {
            m_objects = rhs.m_objects;
        }
        return *this;
    }

    /*------------------------------------------------------------------------------
     * Operator !=
     */
    bool ObjectList::operator!=(const ObjectList &other)
    {
        return !(m_objects == other.m_objects);
    }

    /*------------------------------------------------------------------------------
     * Insert object pointer in list.
     * return EXIT_SUCCESS if ok, else -1.
     * TODO: check if the object already exists in the list and modify the tests.
     */
    int ObjectList::insert(Object *object)
    {
        LM.getLogger()->debug("ObjectList::insert");
        if (m_objects.size() == m_objects.capacity())
        {
            LM.getLogger()->debug("ObjectList::insert - Making list bigger.");
            m_objects.reserve(m_objects.capacity() * 2);
        }
        m_objects.push_back(object);
        std::string msg = "ObjectList::insert - Number of elements in list: " + std::to_string(m_objects.size());
        LM.getLogger()->debug(msg.c_str());
        return EXIT_SUCCESS;
    }

    /*------------------------------------------------------------------------------
     * Remove object pointer from list.
     * return EXIT_SUCCESS if found, else -1.
     * TODO: expect the m_count to be the half and realloc memory?
     */
    int ObjectList::remove(Object *object)
    {
        LM.getLogger()->debug("ObjectList::remove");
        for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
        {
            if (*iter == object)
            {
                m_objects.erase(iter);
                return EXIT_SUCCESS; // Found.
            }
        }
        return EXIT_FAILURE; // Not found.
    }

    /*------------------------------------------------------------------------------
     * Clear list (setting m_count to 0).
     */
    void ObjectList::clear()
    {
        m_objects.clear();
    }

    /*------------------------------------------------------------------------------
     * Return count of objects in list.
     */
    size_t ObjectList::getCount() const
    {
        return m_objects.size();
    }

    /*------------------------------------------------------------------------------
     * Return true if list is empty, else false.
     */
    bool ObjectList::isEmpty() const
    {
        return m_objects.empty();
    }

    /*------------------------------------------------------------------------------
     * Return true if list is full, else false.
     */
    bool ObjectList::isFull() const
    {
        return m_objects.size() == m_objects.capacity();
    }

    /*------------------------------------------------------------------------------
     * Add two lists, second appended to first.
     */
    ObjectList ObjectList::operator+(ObjectList list)
    {
        m_objects.insert(m_objects.end(), list.m_objects.begin(), list.m_objects.end());

        return *this;
    }
}
