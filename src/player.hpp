#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player {
private:
    float m_x, m_y;
    float m_speed;
    int m_points;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Player();
    Player(float width, float height);
    ~Player();
    
    float x() const { return m_x; }
    float y() const { return m_y; }
    int points() const { return m_points; }
    const sf::Sprite& sprite() const { return m_sprite; }

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    void add_points(int points);
};
#endif // __PLAYER_H__