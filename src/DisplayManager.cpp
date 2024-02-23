#include "DisplayManager.h"

#include "LogManager.h"

// Sytem includes

namespace df
{
    // Compute character height, based on window size and font.
    float charHeight()
    {
        // LM.getLogger()->debug("DisplayManager::charHeight: {}", DM.getVerticalPixels() / DM.getVertical());
        return DM.getVerticalPixels() / DM.getVertical();
    }

    // Compute character width, based on window size and font.
    float charWidth()
    {
        // LM.getLogger()->debug("DisplayManager::charWidth: {}", DM.getHorizontalPixels() / DM.getHorizontal());
        return DM.getHorizontalPixels() / DM.getHorizontal();
    }

    // Convert ASCII spaces (x,y) to window pixels (x,y).
    Vector spacesToPixels(Vector spaces)
    {
        // LM.getLogger()->debug("DisplayManager::spacesToPixels: {}, {}", spaces.getX() * charWidth(), spaces.getY() * charHeight());
        return Vector{spaces.getX() * charWidth(), spaces.getY() * charHeight()};
    }

    // Convert window pixels (x,y) to ASCII spaces (x,y).
    Vector pixelsToSpaces(Vector pixels)
    {
        // LM.getLogger()->debug("DisplayManager::pixelsToSpaces");
        return Vector{pixels.getX() / charWidth(), pixels.getY() / charHeight()};
    }

    int DisplayManager::startUp()
    {
        Manager::setType("DisplayManager");
        LM.getLogger()->debug("DisplayManager::startUp");

        m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
        m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;

        m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
        m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;

        sf::RectangleShape *m_p_rectangle; // Backing rectangle for under text.

        if (m_p_window)
        {
            return Manager::startUp();
        }

        m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), "Dragonfly");

        if (!m_p_window)
        {
            LM.getLogger()->debug("Error! Unable to allocate RenderWindow.");
            return -1;
        }

        m_p_window->setMouseCursorVisible(true);
        m_p_window->setVerticalSyncEnabled(true);

        // Load font.
        if (m_font.loadFromFile("./WinterSong.ttf") == false)
        {
            return -1;
        }

        return Manager::startUp();
    }

    void DisplayManager::shutDown()
    {
        LM.getLogger()->debug("DisplayManager::shutDown");
        m_p_window->close();
        delete m_p_window;
        Manager::shutDown();
    }

    int DisplayManager::drawCh(Vector world_pos, char ch, sf::Color color) const
    {
        //LM.getLogger()->debug("DisplayManager::drawCh");
        if (!m_p_window)
        {
            LM.getLogger()->error("Error! Unable to allocate RenderWindow.");
            return -1;
        }

        Vector pixel_pos = spacesToPixels(world_pos);

        static sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
        rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
        rectangle.setPosition(pixel_pos.getX() - charWidth() / 10,
                              pixel_pos.getY() + charHeight() / 5);

        //m_p_window->draw(rectangle);
        static sf::Text text("", m_font);
        text.setString(ch);
        text.setStyle(sf::Text::Bold);

        if (charWidth() < charHeight())
            text.setCharacterSize(charWidth() * 2);
        else
            text.setCharacterSize(charHeight() * 2);

        text.setFillColor(color);

        text.setPosition(pixel_pos.getX(), pixel_pos.getY());
        m_p_window->draw(text);

        return 0;
    }

    /*int DisplayManager::drawFrame(Vector world_pos, Frame frame, bool centered,
                                  Color color) const
    {
    }*/

    int DisplayManager::drawString(Vector world_pos, std::string str, Justification just,
                                   sf::Color color) const
    {
        Vector starting_pos = world_pos;
        switch (just)
        {
        case CENTER_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size() / 2);
            break;
        case RIGHT_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size());
            break;
        case LEFT_JUSTIFIED:
        default:
            break;
        }

        int offset = 0;
        for (auto chr : str)
        {
            Vector temp_pos(starting_pos.getX() + offset, starting_pos.getY());
            drawCh(temp_pos, chr, color);
            offset++;
        }

        return 0;
    }

    // Return window's horizontal maximum (in characters).
    int DisplayManager::getHorizontal() const
    {
        // LM.getLogger()->debug("DisplayManager::getHorizontal: {}", m_window_horizontal_chars);
        return m_window_horizontal_chars;
    }

    // Return window's vertical maximum (in characters).
    int DisplayManager::getVertical() const
    {
        // LM.getLogger()->debug("DisplayManager::getVertical: {}", m_window_vertical_chars);
        return m_window_vertical_chars;
    }

    // Return window's horizontal maximum (in pixels).
    int DisplayManager::getHorizontalPixels() const
    {
        // LM.getLogger()->debug("DisplayManager::getHorizontalPixels: {}", m_window_horizontal_pixels);
        return m_window_horizontal_pixels;
    }

    // Return window's vertical maximum (in pixels).
    int DisplayManager::getVerticalPixels() const
    {
        // LM.getLogger()->debug("DisplayManager::getVerticalPixels: {}", m_window_vertical_pixels);
        return m_window_vertical_pixels;
    }

    // Render current window buffer.
    // Return 0 if ok, else -1.
    int DisplayManager::swapBuffers()
    {
        // LM.getLogger()->debug("DisplayManager::swapBuffers");
        if (!m_p_window)
        {
            LM.getLogger()->debug("Error! Unable to allocate RenderWindow.");
            return -1;
        }

        m_p_window->display();
        m_p_window->clear(m_window_background_color);
        return 0;
    }

    // Return pointer to SFML drawing window.
    sf::RenderWindow *DisplayManager::getWindow() const
    {
        return m_p_window;
    }

    // Set default background color. Return true if ok, else false.
    bool DisplayManager::setBackgroundColor(sf::Color new_color)
    {
        try
        {
            m_window_background_color = new_color;
            return true;
        }
        catch (...)
        {
            LM.getLogger()->debug("DisplayManager::setBackgroundColor");
            return false;
        }
    }
}
