#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"
#include "GameManager.h"

namespace df
{
    int InputManager::startUp()
    {
        if (!DM.isStarted())
            return -1;

        DM.getWindow()->setKeyRepeatEnabled(false);

        return Manager ::startUp();
    }

    void InputManager::shutDown()
    {
        DM.getWindow()->setKeyRepeatEnabled(false);
        Manager::shutDown();
    }

    void InputManager::getInput()
    {
        // Go through all Window events, extracting recognized ones.
        sf::Event event;

        while (DM.getWindow()->pollEvent(event))
        {
            // Key was pressed.
            if (event.type == sf::Event::KeyPressed)
            {
                EventKeyboard *ek = new EventKeyboard();
                ek->setKey(event.key.code);
                ek->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
                LM.getLogger()->debug("InputManager::getInput - KeyPressed: {}", event.key.code);
                Manager::onEvent(ek);
            }

            // Key was released.
            if (event.type == sf::Event::KeyReleased)
            {
                EventKeyboard *keyboardEvent = new EventKeyboard();
                keyboardEvent->setKey(event.key.code);
                keyboardEvent->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
                LM.getLogger()->debug("InputManager::getInput - KeyReleased: {}", event.key.code);
                Manager::onEvent(keyboardEvent);
            }

            // Mouse was moved.
            if (event.type == sf::Event::MouseMoved)
            {
                EventMouse *mouseEvent = new EventMouse();
                mouseEvent->setMouseAction(EventMouseAction::MOVED);
                mouseEvent->setMousePosition(df::Vector{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
                LM.getLogger()->debug("InputManager::getInput - MouseMoved: ({},{})", event.mouseButton.x, event.mouseButton.y);
                Manager::onEvent(mouseEvent);
            }

            // Mouse button pressed.
            //if (event.type == sf::Event::MouseButtonPressed)
            //{
            //}
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            LM.getLogger()->debug("InputManager::getInput - Escape");
            GM.shutDown();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) or sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            EventMouse *mouseEvent = new EventMouse();
            mouseEvent->setMouseButton(event.mouseButton.button);
            mouseEvent->setMouseAction(EventMouseAction::PRESSED);
            mouseEvent->setMousePosition(df::Vector{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
            LM.getLogger()->debug("InputManager::getInput - MouseButtonPressed: {}", event.mouseButton.button);
            Manager::onEvent(mouseEvent);
        }
    }

} // end of namespace df
