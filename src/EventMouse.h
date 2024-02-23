//
// EventMouse - A "mouse" event.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__

#include "Event.h"
#include "Vector.h"
#include <SFML/Window/Mouse.hpp>



namespace df
{

    const std::string MSE_EVENT = "df::mouse";

    // Set of mouse actions recognized by Dragonfly.
    enum EventMouseAction
    {
        UNDEFINED_MOUSE_ACTION = -1,
        CLICKED,
        PRESSED,
        MOVED,
    };

    class EventMouse : public Event
    {

    private:
        EventMouseAction m_mouse_action; // Mouse action.
        sf::Mouse::Button m_mouse_button;    // Mouse button.
        Vector m_mouse_xy;               // Mouse (x,y) coordinates.

    public:
        EventMouse();

        // Set mouse event's action.
        void setMouseAction(EventMouseAction new_mouse_action);

        // Get mouse event's action.
        EventMouseAction getMouseAction() const;

        // Set mouse event's button.
        void setMouseButton(sf::Mouse::Button new_mouse_button);

        // Get mouse event's button.
        sf::Mouse::Button getMouseButton() const;

        // Set mouse event's position.
        void setMousePosition(Vector new_mouse_xy);

        // Get mouse event's position.
        Vector getMousePosition() const;
    };

} // end of namespace df
#endif // __EVENT_MOUSE_H__
