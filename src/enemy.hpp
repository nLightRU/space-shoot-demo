#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Enemy { 
private:
    float m_x, m_y;
    float m_w, m_h;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Enemy();
    Enemy(float x, float y, float w, float h);
    ~Enemy();
    
    float x() const { return m_x; }
    float y() const { return m_y; }
    float w() const { return m_w; }
    float h() const { return m_h; }
    const sf::Sprite& sprite() const { return m_sprite; }

    void move();
};
#endif // __ENEMY_H__