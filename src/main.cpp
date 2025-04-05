#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DEBUG 0

class Drop {
private:
    float m_x, m_y;
    const int m_w, m_h;
    const float m_speed = 3.f;
    // const sf::Color m_color(17, 66, 170);
    sf::RectangleShape m_shape;
public:
    Drop () : m_x(0), m_y(0), m_w(6.f), m_h(15.f), m_shape(sf::RectangleShape(sf::Vector2f(m_w, m_h))) {
        m_shape.setFillColor(sf::Color(17, 66, 170));
        m_shape.setPosition(sf::Vector2f(m_x, m_y));
    }

    Drop(float x, float y) : m_x(x), m_y(y), m_w(6.f), m_h(15.f), m_shape(sf::RectangleShape(sf::Vector2f(m_w, m_h))) {
        m_shape.setFillColor(sf::Color(17, 66, 170));
        m_shape.setPosition(sf::Vector2f(m_x, m_y));
    }

    void move() {
        m_y += Drop::m_speed;
        if(m_y > WINDOW_HEIGHT) {
            m_y = 0;
        }
        m_shape.setPosition(sf::Vector2f(m_x, m_y));
    }

    sf::RectangleShape shape() const {
        return m_shape;
    }

    float y() const { return m_y; } 
};

class Player {
private:
    sf::RectangleShape m_shape;
    sf::Color m_color;
    float m_x, m_y;
    float m_speed;
public:
    Player() : m_x(295.f), m_y(450.f), m_speed(15.f),
                  m_shape(sf::Vector2f(20.f, 20.f)), 
                  m_color(sf::Color::Red)  {
        m_shape.setPosition(m_x, m_y);
    }

    Player(float width, float height) : m_x(295.f), m_y(430.f), m_speed(15.f),
                                           m_shape(sf::Vector2f(width, height)), 
                                           m_color(sf::Color::Red)  {
        m_shape.setPosition(m_x, m_y);
    }

    ~Player() {

    }

    void move_up() {
        m_y -= m_speed;
        m_shape.setPosition(m_x, m_y);
    }

    void move_down() {
        m_y += m_speed;
        m_shape.setPosition(m_x, m_y);
    }

    void move_left() {
        m_x -= m_speed;
        m_shape.setPosition(m_x, m_y);
    }

    void move_right() {
        m_x += m_speed;
        m_shape.setPosition(m_x, m_y);
    }

    void handle(const sf::Event e) {
        if(DEBUG) {
            std::cout << e.key.code << std::endl;
        }
        if(e.key.code == sf::Keyboard::W) {
            this->move_up();
        } else if (e.key.code == sf::Keyboard::A) {
            this->move_left();
        } else if (e.key.code == sf::Keyboard::S) {
            this->move_down();
        } else if (e.key.code == sf::Keyboard::D) {
            this->move_right();
        }
    }

    sf::RectangleShape shape() const { return m_shape; }
};

// void handle(Character& character) {
//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//         std::cout << "W" << std::endl;
//         character.move_up();
//     } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//         std::cout << "A" << std::endl;
//         character.move_left();
//     } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//         std::cout << "S" << std::endl;
//         character.move_down();
//     } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//         std::cout << "D" << std::endl;
//         character.move_right();
//     }
// }

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Moving");
    Player player(50.f, 50.f); 
    window.setFramerateLimit(60);
    
    size_t drops_num = 15;
    int shift = 150;
    std::vector<Drop> drops;
    for(size_t i = 0; i < drops_num; ++i) {
        drops.push_back(Drop(3 + 50 * i, 150 + (50 * i) % shift));
    } 

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) { 
                player.handle(event);
            }
        }
        window.clear();
        for(size_t i = 0; i < drops.size(); ++i) {
            drops[i].move();
            window.draw(drops[i].shape());
        }
        window.draw(player.shape());
        window.display();
    }


    return 0;
}