#include <filesystem>

#include "bullet.hpp"

namespace fs = std::filesystem;

Bullet::Bullet()
{

}

Bullet::Bullet(float x, float y) : 
m_x(x), m_y(y), m_speed(7.f),
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    if(!m_texture.loadFromFile(texture_file.string(), sf::IntRect(807, 236, 5, 10))) {

    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x, m_y);
}

Bullet::~Bullet() 
{

}

void Bullet::move() 
{
    m_y -= m_speed;
    m_sprite.setPosition(m_x, m_y);
}