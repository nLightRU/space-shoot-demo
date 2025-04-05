#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <SFML/Graphics.hpp>

class Enemy { 
private:
    float m_x, m_y;
    float m_w, m_h;
    sf::Color m_color;
    sf::RectangleShape m_shape;
public:
    Enemy();
    Enemy(float x, float y, float w, float h);
    ~Enemy();

    void move();

    sf::RectangleShape shape() const { return m_shape; }
};
#endif // __ENEMY_H__