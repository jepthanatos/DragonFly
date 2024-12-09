#ifndef __MANAGER_H__
#define __MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "Event.h"

namespace df
{

    class Manager
    {

    private:
        std::string m_type; // Manager type identifier.

    protected:
        bool m_is_started; // True if startUp() succeeded.

        // Set type identifier of Manager.
        void setType(std::string new_type);

        // Default constructor.
        Manager();

    public:
        // Default destructor.
        virtual ~Manager();

        // Get type identifier of Manager.
        std::string getType() const;

        // Startup Manager.
        // Return EXIT_SUCCESS if ok, else negative number.
        virtual int startUp();

        // Shutdown Manager.
        virtual void shutDown();

        // Return status of is_started (true when startUp() was successful).
        bool isStarted() const;

        // Send event to all interested Objects.
        // Return count of number of events sent.
        int onEvent(const Event *p_event) const;
    };

} // end of namespace df
#endif // __MANAGER_H__
