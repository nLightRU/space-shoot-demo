#include <filesystem>
#include <iostream>
#include <algorithm>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "config.hpp"
#include "player.hpp"
#include "scene.hpp"

namespace fs = std::filesystem;

int main() { 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Space Shoot");
    window.setFramerateLimit(60);

    int points = 0;

    std::string font_name = "VeniteAdoremus-rgRBA.ttf";
    fs::path font_path = fs::current_path() / "resources" / "fonts" / font_name;
    std::cout << font_path.string() << std::endl;

    sf::Font font;

    if(!font.loadFromFile(font_path.string())) {
        if(DEBUG)
            std::cout << "error loading font" << std::endl;
    }

    sf::Text start_text;

    start_text.setFont(font);
    start_text.setString("Press SPACE for start");
    start_text.setCharacterSize(24);
    start_text.setFillColor(sf::Color(100, 12, 171));
    start_text.setPosition(sf::Vector2f(100.f, 100.f));

    std::string music_filename = "Battle in the Stars.ogg";
    fs::path music_path = fs::current_path() / "resources" / "sounds" / music_filename;
    sf::Music music;
    if(!music.openFromFile(music_path.string())) {
        if(DEBUG)
            std::cout << "Error loading music" << std::endl;
        return -1;
    }

    music.setLoop(true);
    music.setVolume(MUSIC_VOLUME);

    Player* player = new Player(50.f, 50.f);

    sf::Text points_text;
    points_text.setFont(font);
    points_text.setString("Points: " + std::to_string(player->points()));
    points_text.setCharacterSize(12);

    sf::Clock enemies_timer;
    sf::Clock bullets_timer;

    Scene scene(player);

    if(MUSIC)
        music.play();

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
            bool destroy_sound = false;

            points_text.setString("Points: "  + std::to_string(player->points()));
            window.draw(points_text);

            // Draw stars
            for(auto star : scene.stars()) {
                window.draw(star->sprite());
            }
    
            // Draw effects
            for(auto effect : scene.effects()) {
                window.draw(effect->sprite());
                destroy_sound = true;
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
            
            // A try to play sounds
            // TO DO: Refactor this
            for(size_t i = 0; i < scene.sounds().size(); ++i) {
                if(DEBUG) {
                    std::cout << "sound: " << i << " " << "bufer: "<< scene.sounds().at(i)->getBuffer() << std::endl;
                    std::cout << "sounds: " << scene.sounds().size() << std::endl;
                }

                if(scene.sounds().at(i)->getStatus() == sf::SoundSource::Status::Stopped) { 
                    // scene.sounds().at(i)->play();
                }
               
            }
            for(size_t i = 0; i < scene.sounds().size();++i) {
                if(scene.sounds().at(i)->getPlayingOffset().asMilliseconds() >= 1000) {
                    scene.sounds().at(i)->pause();
                    scene.sounds().erase(scene.sounds().begin() + i);
                }
            }
        } else {
            window.draw(start_text);
        }
        
        window.display();
    }

    return 0;
}