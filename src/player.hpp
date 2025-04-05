#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape m_shape;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Color m_color;
    float m_x, m_y;
    float m_speed;
public:
    Player();
    Player(float width, float height);
    ~Player();

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    void handle(const sf::Event e);

    float x() const { return m_x; }
    float y() const { return m_y; }
    sf::Sprite sprite() const { return m_sprite; }
    sf::RectangleShape shape() const { return m_shape; }
};
#endif // __PLAYER_H__