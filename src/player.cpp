#include <iostream>
#include <filesystem>

#include "Player.hpp"

namespace fs = std::filesystem;

Player::Player() : 
m_x(295.f), m_y(450.f), m_speed(15.f), m_points(0),
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    std::cout << texture_file << std::endl;
    m_texture = sf::Texture();
}

Player::Player(float width, float height) : 
m_x(295.f), m_y(430.f), m_speed(15.f), m_points(0),
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    if(DEBUG) {
        std::cout << texture_file << std::endl;
    }
    if(!m_texture.loadFromFile(texture_file.string(), sf::IntRect(800, 256, 20, 20))) {
        if(DEBUG) {
            std::cout << "error loading player texture" << std::endl;
        }
    }
    m_sprite.scale(sf::Vector2f(2.f, 2.f));
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x, m_y);
}

Player::~Player() {

}

void Player::move_up() {
    m_y -= m_speed;
    m_sprite.setPosition(m_x, m_y);
}

void Player::move_down() {
    m_y += m_speed;
    m_sprite.setPosition(m_x, m_y);
}

void Player::move_left() {
    m_x -= m_speed;
    m_sprite.setPosition(m_x, m_y);
}

void Player::move_right() {
    m_x += m_speed;
    m_sprite.setPosition(m_x, m_y);
}

void Player::add_points(int points) {
    m_points += points;
}
