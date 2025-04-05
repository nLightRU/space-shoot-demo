#include "drop.hpp"

Drop::Drop () : m_x(0), m_y(0), m_w(6.f), m_h(15.f), 
                m_shape(sf::RectangleShape(sf::Vector2f(m_w, m_h))) {
    m_shape.setFillColor(sf::Color(17, 66, 170));
    m_shape.setPosition(sf::Vector2f(m_x, m_y));
}

Drop::Drop(float x, float y) : m_x(x), m_y(y), m_w(6.f), m_h(15.f), 
                               m_shape(sf::RectangleShape(sf::Vector2f(m_w, m_h))) {
    m_shape.setFillColor(sf::Color(17, 66, 170));
    m_shape.setPosition(sf::Vector2f(m_x, m_y));
}

void Drop::move() {
    m_y += Drop::m_speed;
    if(m_y > WINDOW_HEIGHT) {
        m_y = 0;
    }
    m_shape.setPosition(sf::Vector2f(m_x, m_y));
}