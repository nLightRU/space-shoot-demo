#include <SFML/System/Clock.hpp>

#include "config.hpp"
#include "Player.hpp"
#include "Scene.hpp"


int main() { 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Space Shoot");
    window.setFramerateLimit(60);

    Player player(50.f, 50.f);

    sf::Clock enemies_timer;
    sf::Clock bullets_timer;

    Scene scene(&player);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            scene.handle_player(event);
        }

        scene.update_scene(event, bullets_timer, enemies_timer);

        window.clear();

        // Draw stars
        for(auto star : scene.stars()) {
            window.draw(star->sprite());
        }

        // Draw effects
        for(auto effect : scene.effects()) {
            window.draw(effect->sprite());
        }

        // Draw player
        window.draw(scene.player()->sprite());

        // Draw bullets
        for(auto bullet : scene.bullets()) {
            window.draw(bullet->sprite());
        }

        // Draw enemies
        for(auto enemy : scene.enemies()) {
            window.draw(enemy->sprite());
        }
        
        window.display();
    }

    return 0;
}