//
// Object - The base game world object.
//
// Copyright 2017, 2019, 2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes.
#include <string>

// Engine includes.
// #include "Animation.h" // Objects (often) have animated sprites.
// #include "Box.h"       // Objects have a bounding box.
#include "Event.h" // Objects can handle events.
// #include "Sprite.h"    // Objects (often) have sprites.
#include "Vector.h" // Objects need a float location.
// Estas las he puesto yo
#include "DisplayManager.h" // Is this needed?
#include "LogManager.h"

namespace df
{

    // Types of solidness of Object.
    enum Solidness
    {
        HARD,     // Object causes collisions and impedes.
        SOFT,     // Object causes collision, but doesn't impede.
        SPECTRAL, // Object doesn't cause collisions.
    };

    class Object
    {

    private:
        int m_id;           // Unique game engine defined identifier.
        std::string m_type; // Game-programmer defined identification.
        // Box m_box;               // Box for sprite boundary & collisions.
        Vector m_position;       // Position in game world.
        Vector m_direction;      // Direction vector.
        float m_speed;           // Object speed in direction.
        std::string sprite_name; // Sprite name in ResourceManager.
        // Animation m_animation;   // Animation associated with Object.
        int m_altitude;        // 0 to MAX_ALTITUDE (higher drawn on top).
        Solidness m_solidness; // Solidness state of Object.

        // const int MAX_ALTITUDE = 4;

    public:
        // Construct Object.
        // Set default parameters and add to game world (WorldManager).
        Object();

        // Destroy object, removing itself from game world (WorldManager).
        virtual ~Object();

        // Set Object id.
        void setId(int new_id);

        // Get Object id.
        int getId() const;

        // Set type identifier of Object.
        void setType(std::string new_type);

        // Get type identifier of Object.
        std::string getType() const;

        // Set position of Object.
        virtual void setPosition(Vector new_position);

        // Get position of Object.
        Vector getPosition() const;

        // Handle event.
        // Base class ignores everything.
        // Return 0 if ignored, else 1.
        virtual int eventHandler(const Event *p_event);

        // Return True if Object is HARD or SOFT, else false.
        bool isSolid() const;

        // Set solidness of Object, with checks for consistency.
        // Return 0 if ok, else -1.
        int setSolidness(Solidness new_solid);

        // Return solidness of Object.
        Solidness getSolidness() const;

        // Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
        // Return 0 if ok, else -1.
        int setAltitude(int new_altitude);

        // Return altitude of Object.
        int getAltitude() const;

        // Set speed of Object.
        void setSpeed(float new_speed);

        // Get speed of Object.
        float getSpeed() const;

        // Set direction of Object.
        void setDirection(Vector new_direction);

        // Get direction of Object.
        Vector getDirection() const;

        // Set direction and speed of Object.
        void setVelocity(Vector new_velocity);

        // Get velocity of Object based on direction and speed.
        Vector getVelocity(); // const;

        // Predict Object position based on speed and direction.
        // Return predicted position.
        Vector predictPosition();

        // Set bounding box of Object.
        // void setBox(Box new_box);

        // Get bounding box of Object.
        // Box getBox() const;

        // Set Sprite for this Object to animate.
        // Return 0 if ok, else -1.
        int setSprite(std::string sprite_label);

        // Set Animation for this Object to new one.
        // Set bounding box to size of associated Sprite.
        // void setAnimation(Animation new_animation);

        // Get Animation for this Object.
        // Animation getAnimation() const;

        // Draw Object Animation.
        virtual int draw()
        {
            //LM.getLogger()->debug("Object::draw");
            DM.drawString(m_position, sprite_name, CENTER_JUSTIFIED, sf::Color::Black);
            return 0;
        };
    };

} // end of namespace df
#endif // __OBJECT_H__
