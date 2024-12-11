#include "Frame.h"

namespace df
{

    Frame::Frame()
    {
        m_width = 0;
        m_height = 0;
        m_frame_str = "";
    }

    Frame::Frame(int new_width, int new_height, std::string frame_str)
    {
        m_width = new_width;
        m_height = new_height;
        m_frame_str = frame_str;
    }

    void Frame::setWidth(int new_width)
    {
        m_width = new_width;
    }

    int Frame::getWidth() const
    {
        return m_width;
    }

    void Frame::setHeight(int new_height)
    {
        m_height = new_height;
    }

    int Frame::getHeight() const
    {
        return m_height;
    }

    void Frame::setString(std::string new_frame_str)
    {
        m_frame_str = new_frame_str;
    }

    std::string Frame::getString() const
    {
        return m_frame_str;
    }

    int Frame::draw(Vector position, sf::Color color, char transparent) const
    {
        if (m_frame_str.empty())
        {
            return -1;
        }

        // Calculate top-left corner.
        int x_offset = m_width / 2;
        int y_offset = m_height / 2;

        // Loop through each row.
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                if (transparent == '\0' or m_frame_str[y * m_width + x] != transparent)
                {
                    Vector temp_pos(position.getX() + x - x_offset, position.getY() + y - y_offset);
                    DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
                }
            }
        }
        return 0;
    }

} // end of namespace df