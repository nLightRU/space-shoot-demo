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
    
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    Star();
    Star(float x, float y);
    
    sf::Sprite sprite() const { return m_sprite; }
    float x() const { return m_x; }
    float y() const { return m_y; } 

    void move();
};
#endif // __DROP_H__
