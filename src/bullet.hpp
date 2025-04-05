#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>

class Bullet
{
private:
    float m_x, m_y;
    float m_speed;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::RectangleShape m_shape;
    sf::Color m_color;
public:
    Bullet();
    Bullet(float x, float y);
    ~Bullet();

    void move();

    float x() const { return m_x; }
    float y() const { return m_y; }
    sf::RectangleShape shape() const { return m_shape; }
    sf::Sprite sprite() { return m_sprite; }
};



#endif // __BULLET_H__