#include <iostream>
#include <filesystem>

#include "player.hpp"

namespace fs = std::filesystem;

Player::Player() : 
m_x(295.f), m_y(450.f), m_speed(15.f),
m_shape(sf::Vector2f(20.f, 20.f)), 
m_color(sf::Color::Red),
m_texture()
{
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    fs::path texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);
    std::cout << texture_file << std::endl;
    m_texture = sf::Texture();
    m_shape.setPosition(m_x, m_y);
}

Player::Player(float width, float height) : 
m_x(295.f), m_y(430.f), m_speed(15.f),
m_shape(sf::Vector2f(width, height)), 
m_color(sf::Color::Red),
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
    m_shape.setPosition(m_x, m_y);
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

void Player::handle(const sf::Event e) {
    if(DEBUG) {
        std::cout << e.key.code << std::endl;
    }
    if(e.key.code == sf::Keyboard::W) {
        this->move_up();
    } else if (e.key.code == sf::Keyboard::A) {
        this->move_left();
    } else if (e.key.code == sf::Keyboard::S) {
        this->move_down();
    } else if (e.key.code == sf::Keyboard::D) {
        this->move_right();
    }
}