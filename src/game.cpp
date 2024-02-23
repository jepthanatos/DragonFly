// Sytem includes.
#include <iostream>
#include <typeinfo>
#include <chrono>
#include <thread>

// Engine includes.
// #include "Manager.h"
#include "GameManager.h"
//#include "WorldManager.h"
// #include "DisplayManager.h"
// #include "EventStep.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include "Object.h"

using namespace df;
using namespace std::chrono_literals;

class Inventado : public Object
{
public:
    Inventado()
    {
        Object::setSprite("*");
        Object::setPosition(df::Vector(10, 5));
        Object::setSolidness(df::Solidness::HARD);
        Object::setAltitude(10);
    }

    int eventHandler(const Event *p_event) override
    {
        //LM.getLogger()->debug("Inventado::eventHandler");
        if (p_event->getType() == KEYBOARD_EVENT)
        {
            const EventKeyboard *ek = dynamic_cast<const EventKeyboard *>(p_event);
            LM.getLogger()->debug("Inventado::eventHandler - KEYBOARD_EVENT");
            if (ek->getKey() == sf::Keyboard::A) {
                DM.setBackgroundColor(sf::Color::Yellow);
            }
            if (ek->getKey() == sf::Keyboard::D) {
                setPosition(df::Vector(15, 5));
            }
            delete ek;
        }
        return 0;
    }
};

int main()
{
    GM.startUp();

    Inventado *i = new Inventado();

    GM.run();
    // DM.startUp();
    // DM.setBackgroundColor(Color::YELLOW);
    // DM.drawCh(df::Vector(10, 5), '*', df::YELLOW);
    // DM.swapBuffers();
    // GM.shutDown();
}