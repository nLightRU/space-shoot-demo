#include "enemy.hpp"

Enemy::Enemy() : 
m_x(0.f), m_y(0.f), m_w(40.f), m_h(40.f), 
m_shape(sf::Vector2f(m_w, m_h)), m_color(sf::Color::Red)
{
    m_shape.setPosition(m_x, m_y);
    m_shape.setFillColor(m_color);
}

Enemy::Enemy(float x, float y, float w, float h) : 
m_x(x), m_y(y), m_w(w), m_h(h), 
m_shape(sf::Vector2f(m_w, m_h)), m_color(sf::Color::Red) 
{
    m_shape.setPosition(m_x, m_y);
    m_shape.setFillColor(m_color);
}

Enemy::~Enemy()
{

}

void Enemy::move()
{

}
