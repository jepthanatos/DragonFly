//
// ResourceManager - The resource manager.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// System includes.
#include <SFML/Audio.hpp>
#include <string>

// Engine includes.
#include "Manager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df
{

// Delimiters used to parse Sprite files -
// the ResourceManager "knows" file format.
#define HEADER_TOKEN "HEADER"
#define BODY_TOKEN "BODY"
#define FOOTER_TOKEN "FOOTER"
#define FRAMES_TOKEN "frames"
#define HEIGHT_TOKEN "height"
#define WIDTH_TOKEN "width"
#define COLOR_TOKEN "color"
#define SLOWDOWN_TOKEN "slowdown"
#define END_FRAME_TOKEN "end"
#define VERSION_TOKEN "version"

  // Maximum number of unique assets in game.
  const int MAX_SPRITES = 1000;
  const int MAX_SOUNDS = 128;
  const int MAX_MUSICS = 128;

  class ResourceManager : public Manager, public Singleton<ResourceManager>
  {
  private:
    Sprite *m_p_sprite[MAX_SPRITES]; // Array of (pointers to) Sprites.
    int m_sprite_count;              // Count of number of loaded sprites.
    Sound m_sound[MAX_SOUNDS];       // Array of sound buffers.
    int m_sound_count;               // Count of number of loaded sounds.
    Music m_music[MAX_MUSICS];       // Array of music buffers.
    int m_music_count;               // Count of number of loaded musics.

    // Remove '\r' from line (if there - typical of Windows).
    void discardCR(std::string &str);

    // Get next line from file, with error checking ("" means error).
    std::string getLine(std::ifstream *p_file);

    // Read in next section of data from file as vector of strings.
    // Return vector (empty if error).
    std::vector<std::string> readData(std::ifstream *p_file, std::string delimiter);

    // Match token in vector of lines (e.g., "frames 5").
    // Return corresponding value (e.g., 5) (-1 if not found).
    // Remove any line that matches from vector.
    int matchLineInt(std::vector<std::string> *p_data, const char *token);

    // Match token in vector of lines (e.g., "color green").
    // Return corresponding string (e.g., "green") ("" if not found).
    // Remove any line that matches from vector.
    std::string matchLineStr(std::vector<std::string> *p_data, const char *token);

    // Match frame lines until "end", clearing all from vector.
    // Return Frame.
    Frame matchFrame(std::vector<std::string> *p_data, int width, int height);

  public:
    // Get ResourceManager ready to manage resources.
    int startUp();

    // Shut down manager, freeing up any allocated Sprites, Music and Sounds.
    void shutDown();

    // Load Sprite from file.
    // Assign indicated label to Sprite.
    // Return 0 if ok, else -1.
    int loadSprite(std::string filename, std::string label);

    // Unload Sprite with indicated label.
    // Return 0 if ok, else -1.
    int unloadSprite(std::string label);

    // Find Sprite with indicated label.
    // Return pointer to it if found, else NULL.
    Sprite *getSprite(std::string label) const;

    // Load sound from file.
    // Return 0 if ok, else -1.
    int loadSound(std::string filename, std::string label);

    // Remove Sound with indicated label.
    // Return 0 if ok, else -1.
    int unloadSound(std::string label);

    // Find Sound with indicated label.
    // Return pointer to it if found, else NULL.
    Sound *getSound(std::string label);

    // Associate file with Music.
    // Return 0 if ok, else -1.
    int loadMusic(std::string filename, std::string label);

    // Remove label for Music with indicated label.
    // Return 0 if ok, else -1.
    int unloadMusic(std::string label);

    // Find Music with indicated label.
    // Return pointer to it if found, else NULL.
    Music *getMusic(std::string label);
  };

} // end of namespace df
#endif //__RESOURCE_MANAGER_H__
