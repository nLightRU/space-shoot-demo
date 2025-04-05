#include "bullet.hpp"

Bullet::Bullet() {

}

Bullet::Bullet(float x, float y) : m_x(x), m_y(y), m_speed(7.f), 
                                  m_shape(sf::Vector2f(10.f, 10.f)), 
                                  m_color(254, 120, 0) {
    m_shape.setPosition(m_x, m_y);
    m_shape.setFillColor(m_color);
}

Bullet::~Bullet() {

}

void Bullet::move() {
    m_y -= m_speed;
    m_shape.setPosition(m_x, m_y);
}