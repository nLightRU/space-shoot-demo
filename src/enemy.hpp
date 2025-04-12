#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Enemy { 
private:
    float m_x, m_y;
    float m_w, m_h;
    int m_damage;

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::Clock m_bullet_timer;
    const float m_bullet_cooldown = 2000.f;
public:
    Enemy();
    Enemy(float x, float y, float w, float h);
    ~Enemy();
    
    float x() const { return m_x; }
    float y() const { return m_y; }
    float w() const { return m_w; }
    float h() const { return m_h; }
    int damage() const { return m_damage; }
    const sf::Sprite& sprite() const { return m_sprite; }

    void setDamage(int damage) { m_damage = damage; }

    bool new_bullet();
    void move();
};
#endif // __ENEMY_H__