#include <iostream>
#include <filesystem>

#include "config.hpp"
#include "Enemy.hpp"

namespace fs = std::filesystem;

Enemy::Enemy() : 
m_x(0.f), m_y(0.f), m_w(40.f), m_h(40.f), 
m_shape(sf::Vector2f(m_w, m_h)), m_color(sf::Color::Red)
{
    m_shape.setPosition(m_x, m_y);
    m_shape.setFillColor(m_color);
}

Enemy::Enemy(float x, float y, float w, float h) : 
m_x(x), m_y(y), m_w(w), m_h(h), 
m_texture(),
m_shape(sf::Vector2f(m_w, m_h)), m_color(198, 0, 124)
{
    // 610 50
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    
    if(!m_texture.loadFromFile(texture_file.string(), sf::IntRect(610, 50, 25, 20))) {
        if(DEBUG) {
            std::cout << "error load enemy texture" << std::endl;
        }
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x, m_y);

    m_shape.setPosition(m_x, m_y);
    m_shape.setFillColor(m_color);
}

Enemy::~Enemy()
{

}

void Enemy::move()
{

}
