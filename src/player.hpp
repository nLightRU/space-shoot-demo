#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Player {
private:
    float m_x, m_y;
    float m_speed;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Player();
    Player(float width, float height);
    ~Player();
    
    float x() const { return m_x; }
    float y() const { return m_y; }
    const sf::Sprite& sprite() const { return m_sprite; }

    void move_up();
    void move_down();
    void move_left();
    void move_right();
};
#endif // __PLAYER_H__