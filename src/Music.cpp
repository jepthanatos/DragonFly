//
// Music - A wrapper for SFML music.
//
// Copyright 2017-2022 by Mark Claypool and WPI
// All Rights Reserved
//

#include "Music.h"

namespace df
{

  Music::Music()
  {
  }

  int Music::loadMusic(const std::string &filename)
  {
    if (!m_music.openFromFile(filename))
    {
      return -1;
    }
    return 0;
  }

  void Music::setLabel(std::string new_label)
  {
    m_label = new_label;
  }

  std::string Music::getLabel() const
  {
    return m_label;
  }

  void Music::play(bool loop)
  {
    m_music.setLoop(loop);
    m_music.play();
  }

  void Music::stop()
  {
    m_music.stop();
  }

  void Music::pause()
  {
    m_music.pause();
  }

  sf::Music *Music::getMusic()
  {
    return &m_music;
  }

} // end of namespace df
