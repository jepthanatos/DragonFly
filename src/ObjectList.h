//
// ObjectList - A list of Objects.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include "Object.h"

namespace df
{

    const int MAX_OBJECTS = 5000;
    const int MAX_COUNT_INIT = 1;

    class ObjectListIterator;

    class ObjectList
    {

    private:
        // Object **p_item; // Array of pointers to objects.
        std::vector<Object *> m_objects;

    public:
        friend class ObjectListIterator; // Iterators can access.

        // Default constructor.
        ObjectList();

        // Destructor.
        ~ObjectList();

        // Copy constructor and operators.
        ObjectList(const ObjectList &other);
        ObjectList &operator=(const ObjectList &rhs);
        bool operator!=(const ObjectList &other);

        // Insert object pointer in list.
        // Return EXIT_SUCCESS if ok, else -1.
        int insert(Object *p_o);

        // Remove object pointer from list,
        // Return EXIT_SUCCESS if found, else -1.
        int remove(Object *p_o);

        // Clear list (setting count to 0).
        void clear();

        // Return count of number of objects in list.
        size_t getCount() const;

        // Return true if list is empty, else false.
        bool isEmpty() const;

        // Return true if list is full, else false.
        bool isFull() const;

        // Add two lists, second appended to first.
        ObjectList operator+(ObjectList list);
    };

} // end of namespace df
#endif // __OBJECT_LIST_H__
