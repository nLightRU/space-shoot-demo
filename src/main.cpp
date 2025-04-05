#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "drop.hpp"
#include "player.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DEBUG 0

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