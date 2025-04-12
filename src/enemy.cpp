#ifdef GAME_DEBUG
#include <iostream>
#endif

#include <filesystem>

#include <SFML/Graphics/Rect.hpp>

#include "config.hpp"
#include "enemy.hpp"

namespace fs = std::filesystem;

Enemy::Enemy() : 
m_x(0.f), m_y(0.f), m_w(40.f), m_h(40.f),
m_damage(20),
m_bullet_timer(),
m_texture()
{

}

Enemy::Enemy(float x, float y, float w, float h) : 
m_x(x), m_y(y), m_w(w), m_h(h), 
m_damage(20),
m_bullet_timer(),
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);

    sf::IntRect r;

    switch (std::rand() % 4) {
    case 0:
        r = sf::IntRect(610, 50, 26, 20);
        break;
    case 1:
        r = sf::IntRect(610, 90, 26, 20);
        break;
    case 2:
        r = sf::IntRect(650, 50, 26, 20);
        break;
    case 3:
        r = sf::IntRect(650, 90, 26, 20);
        break;
    default:
        break;
    }

    if(!m_texture.loadFromFile(texture_file.string(), r)) {
#ifdef GAME_DEBUG
            std::cout << "error load enemy texture" << std::endl;
#endif
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x, m_y);
}

Enemy::~Enemy()
{

}

bool Enemy::new_bullet()
{
    if(m_bullet_timer.getElapsedTime().asMilliseconds() >= m_bullet_cooldown) {
        m_bullet_timer.restart();
        return true;
    }
    return false;
}

void Enemy::move()
{

}
