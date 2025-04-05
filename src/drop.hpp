#ifndef __DROP_H__
#define __DROP_H__
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Drop {
private:
    float m_x, m_y;
    const int m_w, m_h;
    const float m_speed = 3.f;
    // const sf::Color m_color(17, 66, 170);
    sf::RectangleShape m_shape;
public:
    Drop();
    Drop(float x, float y);

    void move();

    sf::RectangleShape shape() const { return m_shape; }
    float y() const { return m_y; } 
};
#endif // __DROP_H__
