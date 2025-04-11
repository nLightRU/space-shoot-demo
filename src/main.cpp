#include <filesystem>
#include <iostream>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>

#include "config.hpp"
#include "Player.hpp"
#include "Scene.hpp"

namespace fs = std::filesystem;

int main() { 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Space Shoot");
    window.setFramerateLimit(60);

    std::string font_name = "VeniteAdoremus-rgRBA.ttf";
    fs::path font_path = fs::current_path() / "resources" / "fonts" / font_name;

    std::cout << font_path.string() << std::endl;

    sf::Font font;

    if(!font.loadFromFile(font_path.string())) {
        std::cout << "error loading font" << std::endl;
    }

    sf::Text text;

    text.setFont(font);
    text.setString("Press SPACE for start");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(100, 12, 171));
    text.setPosition(sf::Vector2f(100.f, 100.f));

    Player player(50.f, 50.f);

    sf::Clock enemies_timer;
    sf::Clock bullets_timer;

    Scene scene(&player);

    bool game_started = false;


    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            
            if(game_started)
                scene.handle_player(event);

            if(event.key.code == sf::Keyboard::Space)
                game_started = true;
        }

        window.clear();

        if(game_started) { 
            scene.update_scene(event, bullets_timer, enemies_timer);

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
        } else {
            window.draw(text);
        }
        
        window.display();
    }

    return 0;
}