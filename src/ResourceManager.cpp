#include "ResourceManager.h"
#include <fstream>
#include <iostream>

namespace df
{
    // Get ResourceManager ready to manage resources.
    int ResourceManager::startUp()
    {
        m_sprite_count = 0;
        Manager::startUp();
        return 0;
    }

    // Shut down manager, freeing up any allocated Sprites, Music and Sounds.
    void ResourceManager::shutDown()
    {
        for (int i = 0; i < m_sprite_count; i++)
        {
            delete m_p_sprite[i];
        }
        Manager::shutDown();
    }

    // Remove '\r' from line (if there - typical of Windows).
    void ResourceManager::discardCR(std::string &str)
    {
        if (str.size() > 0 && str[str.size() - 1] == '\r')
        {
            str.erase(str.size() - 1);
        }
    }

    // Get next line from file, with error checking ("" means error).
    std::string ResourceManager::getLine(std::ifstream *p_file)
    {
        std::string line;
        std::getline(*p_file, line);
        if (!p_file->good())
        {
            return "";
        }
        return line;
    }

    // Read in next section of data from file as vector of strings.
    // Return vector (empty if error).
    std::vector<std::string> ResourceManager::readData(std::ifstream *p_file, std::string delimiter)
    {
        std::string beginning = "<" + delimiter + ">"; // Section beginning
        std::string ending = "</" + delimiter + ">";   // Section ending

        // Check for beginning.
        std::string s = getLine(p_file);
        if (s != beginning)
        {
            return {}; // Return empty vector if error
        }

        std::vector<std::string> data;

        // Read in data until ending (or not found).
        s = getLine(p_file);
        while (s != ending && !s.empty())
        {
            data.push_back(s);
            s = getLine(p_file);
        }

        // If ending not found, then error.
        if (s.empty())
        {
            return {}; // Return empty vector if error
        }

        return data;
    }

    // Match token in vector of lines (e.g., "frames 5").
    // Return corresponding value (e.g., 5) (-1 if not found).
    // Remove any line that matches from vector.
    int ResourceManager::matchLineInt(std::vector<std::string> *p_data, const char *token)
    {
        // Loop through all lines.
        auto i = p_data->begin(); // Vector iterator
        while (i != p_data->end())
        {
            if (i->find(token) != std::string::npos)
            {
                int number = std::atoi(i->substr(strlen(token)).c_str());
                i = p_data->erase(i); // Clear from vector
                return number;
            }
            else
            {
                ++i;
            }
        }
        return -1;
    }

    std::string ResourceManager::matchLineStr(std::vector<std::string> *p_data, const char *token)
    {
        // Loop through all lines.
        auto i = p_data->begin(); // Vector iterator
        while (i != p_data->end())
        {
            if (i->find(token) != std::string::npos)
            {
                return i->substr(strlen(token) + 1);
            }
            else
            {
                ++i;
            }
        }
        return "";
    }

    // Match frame lines until "end", clearing all from vector.
    // Return Frame (empty if error).
    Frame ResourceManager::matchFrame(std::vector<std::string> *p_data, int width, int height)
    {
        std::string line, frame_str;

        for (int h = 0; h < height; ++h)
        {
            line = p_data->front();

            if (line.length() != width)
            {
                return Frame(); // Return empty frame if error
            }

            p_data->erase(p_data->begin());
            frame_str += line;
        }

        line = p_data->front();
        if (line != END_FRAME_TOKEN)
        {
            return Frame(); // Return empty frame if error
        }
        p_data->erase(p_data->begin());

        Frame frame(width, height, frame_str);
        return frame;
    }

    // Load Sprite from file.
    // Assign indicated label to Sprite.
    // Return 0 if ok, else -1.
    int ResourceManager::loadSprite(std::string filename, std::string label)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            return -1;
        }

        // Get line from file
        std::string line = getLine(&file);
        int frame_count, width, height, slowdown;
        sf::Color color;

        auto loadRobustSprite = []() -> void {

        };
        auto loadSimpleSprite = [&]() -> void
        {
            // Read sprite header
            std::getline(file, line);
            frame_count = std::stoi(line);

            std::getline(file, line);
            width = std::stoi(line);

            std::getline(file, line);
            height = std::stoi(line);

            std::getline(file, line);
            slowdown = std::stoi(line);

            std::getline(file, line);
            if (line == "black")
            {
                color = sf::Color::Black;
            }
            else if (line == "red")
            {
                color = sf::Color::Red;
            } // Add more colors as needed

            // Create new sprite
            Sprite *sprite = new Sprite(frame_count);
            sprite->setWidth(width);
            sprite->setHeight(height);
            sprite->setSlowdown(slowdown);
            sprite->setColor(color);

            // Read and add frames to sprite
            for (int f = 0; f < frame_count; ++f)
            {
                Frame frame;
                std::string frame_str;
                for (int h = 0; h < height; ++h)
                {
                    std::getline(file, line);
                    // Add line to frame string
                    frame_str += line;
                }
                frame.setWidth(width);
                frame.setHeight(height);
                frame.setString(frame_str);
                sprite->addFrame(frame);
            }

            // Add label to sprite
            sprite->setLabel(label);

            m_p_sprite[m_sprite_count] = sprite;
            m_sprite_count++;
        };

        if (line == "<HEADER>")
        {
            loadRobustSprite();
        }
        else if (std::atoi(line.c_str()) > 0)
        {
            loadSimpleSprite();
        }
        else
        {
            // Uknown error
        }

        file.close();

        return 0;
    }

    // Unload Sprite with indicated label.
    // Return 0 if ok, else -1.
    int ResourceManager::unloadSprite(std::string label)
    {
        for (int i = 0; i < m_sprite_count; i++)
        {
            if (m_p_sprite[i]->getLabel() == label)
            {
                delete m_p_sprite[i];
                m_p_sprite[i] = m_p_sprite[m_sprite_count - 1];
                m_sprite_count--;
                return 0;
            }
        }
        return -1;
    }

    // Find Sprite with indicated label.
    // Return pointer to it if found, else NULL.
    Sprite *ResourceManager::getSprite(std::string label) const
    {
        for (int i = 0; i < m_sprite_count; i++)
        {
            if (m_p_sprite[i]->getLabel() == label)
            {
                return m_p_sprite[i];
            }
        }
        return nullptr;
    }

    // Load sound from file.
    // Return 0 if ok, else -1.
    // int ResourceManager::loadSound(std::string filename, std::string label)
    // {
    //     if (m_sound_count >= MAX_SOUNDS)
    //     {
    //         return -1;
    //     }
    //     if (m_sound[m_sound_count].loadSound(filename) == 0)
    //     {
    //         m_sound[m_sound_count].setLabel(label);
    //         m_sound_count++;
    //         return 0;
    //     }
    //     return -1;
    // }

    // Remove Sound with indicated label.
    // Return 0 if ok, else -1.
    // int ResourceManager::unloadSound(std::string label)
    // {
    //     for (int i = 0; i < m_sound_count; i++)
    //     {
    //         if (m_sound[i].getLabel() == label)
    //         {
    //             m_sound[i] = m_sound[m_sound_count - 1];
    //             m_sound_count--;
    //             return 0;
    //         }
    //     }
    //     return -1;
    // }

    // Find Sound with indicated label.
    // Return pointer to it if found, else NULL.
    // Sound *ResourceManager::getSound(std::string label)
    // {
    //     for (int i = 0; i < m_sound_count; i++)
    //     {
    //         if (m_sound[i].getLabel() == label)
    //         {
    //             return &m_sound[i];
    //         }
    //     }
    //     return nullptr;
    // }

    // Associate file with Music.
    // Return 0 if ok, else -1.
    // int ResourceManager::loadMusic(std::string filename, std::string label)
    // {
    //     if (m_music_count >= MAX_MUSICS)
    //     {
    //         return -1;
    //     }
    //     if (m_music[m_music_count].loadMusic(filename) == 0)
    //     {
    //         m_music[m_music_count].setLabel(label);
    //         m_music_count++;
    //         return 0;
    //     }
    //     return -1;
    // }

    // Remove label for Music with indicated label.
    // Return 0 if ok, else -1.
    // int ResourceManager::unloadMusic(std::string label)
    // {
    //     for (int i = 0; i < m_music_count; i++)
    //     {
    //         if (m_music[i].getLabel() == label)
    //         {
    //             m_music[i] = m_music[m_music_count - 1];
    //             m_music_count--;
    //             return 0;
    //         }
    //     }
    //     return -1;
    // }

    // Find Music with indicated label.
    // Return pointer to it if found, else NULL.
    // Music *ResourceManager::getMusic(std::string label)
    // {
    //     for (int i = 0; i < m_music_count; i++)
    //     {
    //         if (m_music[i].getLabel() == label)
    //         {
    //             return &m_music[i];
    //         }
    //     }
    //     return nullptr;
    // }

} // end of namespace df
