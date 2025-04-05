#ifndef __STAR_H__
#define __STAR_H__
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Star {
private:
    float m_x, m_y;
    const float m_w, m_h;
    const float m_speed = 2.f;
    // const sf::Color m_color(17, 66, 170);
    sf::RectangleShape m_shape;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Star();
    Star(float x, float y);

    void move();

    sf::RectangleShape shape() const { return m_shape; }
    sf::Sprite sprite() const { return m_sprite; }
    float y() const { return m_y; } 
};
#endif // __DROP_H__
