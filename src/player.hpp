#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player {
private:
    float m_x, m_y;
    float m_w, m_h;
    float m_speed;
    int m_health;
    int m_points;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Player();
    Player(float width, float height);
    ~Player();
    
    float x() const { return m_x; }
    float y() const { return m_y; }
    float w() const { return m_w; } 
    float h() const { return m_h; }
    int health() const { return m_health; }
    int points() const { return m_points; }
    const sf::Sprite& sprite() const { return m_sprite; }

    void apply_damage(int damage);

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    void set_points(int points) { m_points = points;}
    void set_health(int health) { m_health = health; }
    void add_points(int points);
};
#endif // __PLAYER_H__