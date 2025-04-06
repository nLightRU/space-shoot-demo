#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "Star.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

bool check_collision(const Bullet* b, Enemy* e) {
    if(b->x() > e->x() && b->x() < (e->x() + e->w())) {
        if(b->y() > e->y() && b->y() < (e->y() + e->h())) {
            return true;
        }
    }
    return false;
}

void handle_bullets(std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies) {
    for(size_t i = 0; i < bullets.size(); ++i) {
        bool collision = false;
        bullets[i]->move();
        for(size_t j = 0; j < enemies.size(); ++j) {
            if(check_collision(bullets[i], enemies[j])) {
                bullets.erase(bullets.begin() + i);    
                enemies.erase(enemies.begin() + j);
                collision = true;
                continue;
            }
        }
        if(collision) {
            continue;
        } else if(bullets[i]->y() > WINDOW_HEIGHT ) {
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
    std::vector<Star*> stars;
    for(size_t i = 0; i < drops_num; ++i) {
        float star_x = 20 + rand() % 640;
        float star_y = rand() % 400;
        stars.push_back(new Star(star_x, star_y));
    }

    Player player(50.f, 50.f); 
    
    sf::Clock enemies_timer;
    size_t enemies_num = 6;
    std::vector<Enemy*> enemies;

    sf::Clock bullets_timer;
    std::vector<Bullet*> bullets;

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
            bullets.push_back(new Bullet(player.x() + 17.f, player.y() - 20.f));
            bullets_timer.restart();
        }

        if(enemies_timer.getElapsedTime().asSeconds() > 2.f && enemies.size() < enemies_num ) {
            float x = rand() % 500;
            float y = rand() % 100;
            enemies.push_back(new Enemy(x, y, 40.f, 30.f));
            enemies_timer.restart();
        }

        handle_bullets(bullets, enemies);

        window.clear();
        for(size_t i = 0; i < stars.size(); ++i) {
            stars[i]->move();
            window.draw(stars[i]->sprite());
        }

        for(size_t i = 0; i < bullets.size(); ++i) {
            window.draw(bullets[i]->sprite());
        }

        for(size_t i = 0; i < enemies.size(); ++i) {
            window.draw(enemies[i]->sprite());
        }

        window.draw(player.sprite());
        window.display();
    }

    return 0;
}