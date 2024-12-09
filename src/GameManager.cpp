//============================================================================
// Name        : GameManager.cpp
// Author      : Jorge
// Copyright   : https://creativecommons.org/licenses/by/4.0/
// Description : Manager of the game loop.
//============================================================================

#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ObjectListIterator.h"
#include "Clock.h"
#include "EventStep.h"

#include <thread>

//==============================================================================
/* Manager */
//==============================================================================

namespace df
{

    /*------------------------------------------------------------------------------
     * Start up the GameManager services.
     */
    int GameManager::startUp()
    {
        Manager::setType("GameManager");
        if (LM.startUp() == 0)
        {
            LM.getLogger()->debug("GameManager::startUp");
            if (DM.startUp() == 0 and IM.startUp() == 0)
            {
                if (WM.startUp() == 0)
                {
                    setGameOver(false);
                    return Manager::startUp();
                }
            }
        }
        return EXIT_FAILURE;
    }

    bool GameManager::isValid(std::string event_name) const
    {
        if (event_name == STEP_EVENT)
            return true;
        else
            return false;
    }

    /*------------------------------------------------------------------------------
     * Shut down the GameManager services.
     */
    void GameManager::shutDown()
    {
        setGameOver(true);
        Manager::shutDown();
        IM.shutDown();
        WM.shutDown();
        LM.getLogger()->debug("GameManager::shutDown");
        LM.shutDown();
    }

    /*------------------------------------------------------------------------------
     * Run game loop.
     */
    void GameManager::run()
    {
        LM.getLogger()->debug("GameManager::run - Trying to run the game");

        const std::chrono::milliseconds TARGET_TIME{33};

        Clock clock;
        std::chrono::milliseconds loopTime, adjustTime, intendedSleepTime, actualSleepTime;

        ObjectList worldObjects;
        Event *e = new EventStep();

        while (!m_game_over)
        {
            // LM.getLogger()->debug("GameManager::run - Inside game loop");

            clock.delta();

            Manager::onEvent(e);
            IM.getInput();
            WM.update();
            WM.draw();
            DM.swapBuffers();

            loopTime = clock.split();
            intendedSleepTime = TARGET_TIME - loopTime - adjustTime;
            clock.delta();
            std::this_thread::sleep_for(intendedSleepTime);

            actualSleepTime = clock.split();
            adjustTime = actualSleepTime - intendedSleepTime;
            if (adjustTime < std::chrono::milliseconds(0))
                adjustTime = std::chrono::milliseconds(0);
        }

        LM.getLogger()->debug("GameManager::run - Ending game loop");
    }

    /*------------------------------------------------------------------------------
     * Set game over status to indicated value.
     * If true (default), will stop game loop.
     */
    void GameManager::setGameOver(bool value)
    {
        std::string state = value ? "true" : "false";
        std::string msg = "GameManager::setGameOver - Setting m_game_over to = " + state;
        LM.getLogger()->debug(msg.c_str());
        m_game_over = value;
    }

    /*------------------------------------------------------------------------------
     * Get game over status.
     */
    bool GameManager::getGameOver() const
    {
        return m_game_over;
    }

    /*------------------------------------------------------------------------------
     * Return frame time.
     * Frame time is target time for game loop, in miliseconds.
     */
    int GameManager::getFrameTime() const
    {
        // return frameTime;
        return EXIT_SUCCESS;
    }

    int GameManager::getStepCount() const
    {
        return m_step_count;
    }
}
