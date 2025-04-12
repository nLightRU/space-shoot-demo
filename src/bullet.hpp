#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// TODO: add damage to the Bullet class
class Bullet
{
private:
    float m_x, m_y;
    float m_speed;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Bullet();
    Bullet(float x, float y, bool is_player = true);
    ~Bullet();

    float x() const { return m_x; }
    float y() const { return m_y; }
    const sf::Sprite& sprite() { return m_sprite; }

    void move();
};



#endif // __BULLET_H__