//
// EventKeyboard - A "keyboard" event.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

#include "Event.h"
#include <SFML/Window/Keyboard.hpp>

namespace df
{

    const std::string KEYBOARD_EVENT = "df::keyboard";

    // Types of keyboard actions Dragonfly recognizes.
    enum EventKeyboardAction
    {
        UNDEFINED_KEYBOARD_ACTION = -1, // Undefined.
        KEY_PRESSED,                    // Was down.
        KEY_RELEASED,                   // Was released.
        KEY_DOWN,                       // Is down.
    };

    class EventKeyboard : public Event
    {

    private:
        sf::Keyboard::Key m_key_val;           // Key value.
        EventKeyboardAction m_keyboard_action; // Key action.

    public:
        EventKeyboard();

        // Set key in event.
        void setKey(sf::Keyboard::Key new_key);

        // Get key from event.
        sf::Keyboard::Key getKey() const;

        // Set keyboard event action.
        void setKeyboardAction(EventKeyboardAction new_action);

        // Get keyboard event action.
        EventKeyboardAction getKeyboardAction() const;
    };

} // end of namespace df
#endif // __EVENT_KEYBOARD_H__
