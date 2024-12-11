//
// Sprite - The sprite.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

// System includes.
#include <string>

// Engine includes.
// #include "Color.h"
#include "Frame.h"

namespace df
{

  class Sprite
  {

  private:
    int m_width;           // Sprite width.
    int m_height;          // Sprite height.
    int m_max_frame_count; // Maximum number of frames sprite can have.
    int m_frame_count;     // Actual number of frames sprite has.
    sf::Color m_color;     // Optional color for entire sprite.
    int m_slowdown;        // Animation slowdown (1 = no slowdown, 0 = stop).
    Frame *m_frame;        // Array of frames.
    std::string m_label;   // Text label to identify sprite.
    Sprite();              // Sprite constructor always has one arg.
    char m_transparency;   // Sprite transparent character (0 if none)

  public:
    // Delete sprite, removing any allocated frames.
    ~Sprite();

    // Create sprite with indicated maximum number of frames.
    Sprite(int max_frames);

    // Set width of sprite.
    void setWidth(int new_width) { m_width = new_width; }

    // Get width of sprite.
    int getWidth() const { return m_width; }

    // Set height of sprite.
    void setHeight(int new_height) { m_height = new_height; }

    // Get height of sprite.
    int getHeight() const { return m_height; }

    // Set sprite color.
    void setColor(sf::Color new_color) { m_color = new_color; }

    // Get sprite color.
    sf::Color getColor() const { return m_color; }

    // Get total count of frames in sprite.
    int getFrameCount() const { return m_frame_count; }

    // Add frame to sprite.
    // Return -1 if frame array full, else 0.
    int addFrame(Frame new_frame);

    // Get next sprite frame indicated by number.
    // Return empty frame if out of range [0, m_frame_count − 1].
    Frame getFrame(int frame_number) const;

    // Set label associated with sprite.
    void setLabel(std::string new_label) { m_label = new_label; }

    // Get label associated with sprite.
    std::string getLabel() const { return m_label; }

    // Set animation slowdown value.
    // Value in multiples of GameManager frame time.
    void setSlowdown(int new_sprite_slowdown) { m_slowdown = new_sprite_slowdown; }

    // Get animation slowdown value.
    // Value in multiples of GameManager frame time.
    int getSlowdown() const { return m_slowdown; }

    // Draw indicated frame centered at position (x,y).
    // Return 0 if ok, else -1.
    // Note: top-left coordinate is (0,0).
    int draw(int frame_number, Vector position) const;

    // Set sprite transparency character (0 means none)
    void setTransparency(char new_transparency) { m_transparency = new_transparency; }

    // Get sprite transparency character (0 means none)
    char getTransparency() const { return m_transparency; }
  };

} // end of namespace df
#endif // __SPRITE_H__
