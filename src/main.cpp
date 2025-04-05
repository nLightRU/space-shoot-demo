#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "drop.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "enemy.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DEBUG 0

void handle_bullets(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies) {
    for(size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].move();
        if(bullets[i].y() > WINDOW_HEIGHT ) {
            bullets.erase(bullets.begin() + i);
        }
    }
   
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Moving");
    window.setFramerateLimit(60);
    srand(time({}));
    
    size_t drops_num = 200;
    int shift = 150;
    std::vector<Drop> drops;
    for(size_t i = 0; i < drops_num; ++i) {
        float drop_x = 20 + rand() % 640;
        float drop_y = rand() % 400;
        drops.push_back(Drop(drop_x, drop_y));
    }

    Player player(50.f, 50.f); 
    
    sf::Clock enemies_timer;
    size_t enemies_num = 6;
    std::vector<Enemy> enemies;

    sf::Clock bullets_timer;
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

        if(enemies_timer.getElapsedTime().asSeconds() > 2.f && enemies.size() < enemies_num ) {
            enemies.push_back(Enemy());
        }

        handle_bullets(bullets, enemies);

        window.clear();
        for(size_t i = 0; i < drops.size(); ++i) {
            drops[i].move();
            window.draw(drops[i].shape());
        }

        for(size_t i = 0; i < bullets.size(); ++i) {
            window.draw(bullets[i].shape());
        }

        for(size_t i = 0; i < enemies.size(); ++i) {
            window.draw(enemies[i].shape());
        }

        window.draw(player.shape());
        window.display();
    }

    return 0;
}