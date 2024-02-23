#include "Object.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"

namespace df
{
    Object::Object()
    {
        // Set default parameters.
        static int cont{0};
        m_id = cont;
        ++cont;
        m_type = "Object";
        // m_box = Box();
        m_position = Vector();
        m_direction = Vector();
        m_speed = 0;
        sprite_name = "";
        // m_animation = Animation();
        m_altitude = MAX_ALTITUDE / 2; // Default altitude
        m_solidness = HARD;

        // Add to game world.
        if (WM.insertObject(this) == 0)
        {

            std::string msg = "Object::Constructor : " + std::to_string(m_id);
            LM.getLogger()->debug(msg.c_str());
        }
        else
        {
            std::string msg = "Object::Constructor : Error object " + std::to_string(m_id);
            LM.getLogger()->error(msg.c_str());
        }
    }

    Object::~Object()
    {
        // Remove object from game world.
        if (WM.removeObject(this) == 0)
        {
            LM.getLogger()->debug("Object::Destructor : {}", m_id);
        }
        else
        {
            LM.getLogger()->error("Error removing object: {}", m_id);
        }
    }

    void Object::setId(int new_id)
    {
        m_id = new_id;
    }

    int Object::getId() const
    {
        return m_id;
    }

    void Object::setType(std::string new_type)
    {
        m_type = new_type;
    }

    std::string Object::getType() const
    {
        return m_type;
    }

    void Object::setPosition(Vector new_position)
    {
        m_position = new_position;
        // set the box position to the new position
        // m_box.setCorner(m_position);
    }

    Vector Object::getPosition() const
    {
        return m_position;
    }

    int Object::eventHandler(const Event *p_event)
    {
        // Base class ignores all events.
        if (p_event->getType() == UNDEFINED_EVENT)
        {
            LM.getLogger()->debug("Object::eventHandler - UNDEFINED_EVENT");
        }
        if (p_event->getType() == STEP_EVENT)
        {
            // LM.getLogger()->debug("Object::eventHandler - STEP_EVENT");
        }
        return 0;
    }

    bool Object::isSolid() const
    {
        return (m_solidness == HARD || m_solidness == SOFT);
    }

    int Object::setSolidness(Solidness new_solid)
    {
        // Check for invalid solidness.
        if (new_solid != HARD && new_solid != SOFT && new_solid != SPECTRAL)
        {
            return -1;
        }
        else
        {
            m_solidness = new_solid;
            return 0;
        }
    }

    Solidness Object::getSolidness() const
    {
        return m_solidness;
    }

    int Object::setAltitude(int new_altitude)
    {
        if (new_altitude < 0 || new_altitude > MAX_ALTITUDE)
        {
            LM.getLogger()->debug("Invalid altitude value: {}", new_altitude);
            return -1;
        }
        m_altitude = new_altitude;
        return 0;
    }

    int Object::getAltitude() const
    {
        return m_altitude;
    }

    void Object::setSpeed(float new_speed)
    {
        m_speed = new_speed;
    }

    float Object::getSpeed() const
    {
        return m_speed;
    }

    void Object::setDirection(Vector new_direction)
    {
        m_direction = new_direction;
    }

    Vector Object::getDirection() const
    {
        return m_direction;
    }

    void Object::setVelocity(Vector new_velocity)
    {
        m_direction = new_velocity;
        m_speed = m_direction.getMagnitude();
        m_direction.normalize();
    }

    Vector Object::getVelocity() // const
    {
        m_direction.scale(m_speed);
        return m_direction;
    }

    Vector Object::predictPosition()
    {
        return Vector{m_position + getVelocity()};
    }

    /*void Object::setBox(Box new_box)
    {
        m_box = new_box;
    }

    Box Object::getBox() const
    {
        return m_box;
    }*/

    int Object::setSprite(std::string sprite_label)
    {
        sprite_name = sprite_label;
        return 0;
    }

    /*void Object::setAnimation(Animation new_animation)
    {
        m_animation = new_animation;
        m_box = m_animation.getSprite()->getBox();
    }

    Animation Object::getAnimation() const
    {
        return m_animation;
    }

    int Object::draw()
    {
        if (!m_animation)
            return -1;
        Vector pos = getPosition();
        pos.setX(pos.getX() - m_animation.getSprite()->getWidth() / 2);
        pos.setY(pos.getY() - m_animation.getSprite()->getHeight() / 2);
        m_animation.draw(pos);
        return 0;
    }*/
}