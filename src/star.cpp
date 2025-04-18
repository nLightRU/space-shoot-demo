#include <filesystem>

#include "config.hpp"
#include "star.hpp"

namespace fs = std::filesystem;

Star::Star () : m_x(0), m_y(0), m_w(4.5f), m_h(4.5f)
{

}

Star::Star(float x, float y) : 
m_x(x), m_y(y), m_w(4.5f), m_h(4.5f), 
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    if(!m_texture.loadFromFile(texture_file.string(), sf::IntRect(892, 189, 4, 4))) {

    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x, m_y);
}

void Star::move() {
    m_y += m_speed;
    if(m_y > WINDOW_HEIGHT) {
        m_y = 0;
    }
    m_sprite.setPosition(sf::Vector2f(m_x, m_y));
}