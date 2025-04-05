#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "drop.hpp"
#include "bullet.hpp"
#include "player.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DEBUG 0

void move_bullets(std::vector<Bullet>& bullets) {
    for(size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].move();
        if(bullets[i].y() > WINDOW_HEIGHT ) {
            bullets.erase(bullets.begin() + i);
        }
    }
   
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Moving");
    Player player(50.f, 50.f); 
    window.setFramerateLimit(60);
    
    sf::Clock bullets_timer;
    
    size_t drops_num = 15;
    int shift = 150;
    std::vector<Drop> drops;
    for(size_t i = 0; i < drops_num; ++i) {
        drops.push_back(Drop(3 + 50 * i, 150 + (50 * i) % shift));
    }

    size_t bullets_num = 0;
    std::vector<Bullet> bullets;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) { 
                player.handle(event);
            }

        }
        
        if(bullets_timer.getElapsedTime().asMilliseconds() > 500.f) {
            bullets.push_back(Bullet(player.x(), player.y() - 50.f));
            bullets_timer.restart();
        }

        move_bullets(bullets);

        window.clear();
        for(size_t i = 0; i < drops.size(); ++i) {
            drops[i].move();
            window.draw(drops[i].shape());
        }

        for(size_t i = 0; i < bullets.size(); ++i) {
            window.draw(bullets[i].shape());
        }

        window.draw(player.shape());
        window.display();
    }

    return 0;
}