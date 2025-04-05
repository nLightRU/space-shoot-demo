#include <iostream>

#include "player.hpp"

Player::Player() : m_x(295.f), m_y(450.f), m_speed(15.f),
                m_shape(sf::Vector2f(20.f, 20.f)), 
                m_color(sf::Color::Red)  {
    m_shape.setPosition(m_x, m_y);
}

Player::Player(float width, float height) : m_x(295.f), m_y(430.f), m_speed(15.f),
                                        m_shape(sf::Vector2f(width, height)), 
                                        m_color(sf::Color::Red)  {
    m_shape.setPosition(m_x, m_y);
}

Player::~Player() {

}

void Player::move_up() {
    m_y -= m_speed;
    m_shape.setPosition(m_x, m_y);
}

void Player::move_down() {
    m_y += m_speed;
    m_shape.setPosition(m_x, m_y);
}

void Player::move_left() {
    m_x -= m_speed;
    m_shape.setPosition(m_x, m_y);
}

void Player::move_right() {
    m_x += m_speed;
    m_shape.setPosition(m_x, m_y);
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