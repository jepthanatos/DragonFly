//
// InputManager - the SFML input manager.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "Manager.h"
#include "Singleton.h"

// Two-letter acronym for easier access to manager.
#define IM df::InputManager::getInstance()

namespace df
{

    class InputManager : public Manager, public Singleton<InputManager>
    {
    public:
        // Get window ready to capture input.
        // Return EXIT_SUCCESS if ok, else return EXIT_FAILURE;
        int startUp();

        // Revert back to normal window mode.
        void shutDown();

        // Get input from the keyboard and mouse.
        // Pass event along to all interested Objects.
        void getInput();
    };

} // end of namespace df
#endif //__INPUT_MANAGER_H__
