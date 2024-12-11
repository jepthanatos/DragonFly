#include "Sprite.h"

namespace df
{
    Sprite::Sprite(int max_frames) : m_frame_count{0},
                                     m_width{0},
                                     m_height{0},
                                     m_max_frame_count{max_frames},
                                     m_color{COLOR_DEFAULT}
    {
        m_frame = new Frame[max_frames];
    }

    Sprite::~Sprite()
    {
        if (m_frame != NULL)
            delete[] m_frame;
    }

    int Sprite::addFrame(Frame new_frame)
    {
        if (m_frame_count == m_max_frame_count)
        {
            return -1;
        }
        else
        {
            m_frame[m_frame_count] = new_frame;
            m_frame_count++;
            return 0;
        }
    }

    Frame Sprite::getFrame(int frame_number) const
    {
        if (frame_number < 0 || frame_number >= m_frame_count)
        {
            Frame empty;
            return empty;
        }
        return m_frame[frame_number];
    }
}