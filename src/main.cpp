#ifdef GAME_DEBUG
#include <iostream>
#endif

#include <filesystem>
// #include <algorithm>

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
#ifdef GAME_DEBUG
    std::cout << font_path.string() << std::endl;
#endif

    sf::Font font;

    if(!font.loadFromFile(font_path.string())) {
#ifdef GAME_DEBUG
            std::cout << "error loading font" << std::endl;
#endif
    }
    
    sf::Text game_title_text;
    std::string game_title_text_str = "SPACE SHOOT v0.2.0";
    size_t game_title_text_characters_size = 24;
    sf::Color game_title_text_color(254, 101, 1);
    game_title_text.setFont(font);
    game_title_text.setString(game_title_text_str);
    game_title_text.setCharacterSize(game_title_text_characters_size);
    game_title_text.setFillColor(game_title_text_color);
    game_title_text.setPosition(
        sf::Vector2f(
            (WINDOW_WIDTH - game_title_text.getLocalBounds().getSize().x) / 2,
            (WINDOW_HEIGHT - game_title_text_characters_size) / 4
        )
    );


    sf::Text press_start_text;
    std::string press_start_text_str = "Press SPACE for start";
    size_t start_text_charachers_size = 20;
    sf::Color press_start_text_color(100, 12, 171);
    press_start_text.setFont(font);
    press_start_text.setString(press_start_text_str);
    press_start_text.setCharacterSize(start_text_charachers_size);
    press_start_text.setFillColor(press_start_text_color);
       

    sf::Text game_over_text;
    std::string game_over_text_str = "GAME OVER";
    size_t game_over_text_characters_size = 24;
    sf::Color game_over_text_color(179, 45, 69);
    game_over_text.setFont(font);
    game_over_text.setString(game_over_text_str);
    game_over_text.setCharacterSize(game_over_text_characters_size);
    game_over_text.setFillColor(game_over_text_color);
    game_over_text.setPosition(
        sf::Vector2f(
            (WINDOW_WIDTH - game_over_text.getLocalBounds().getSize().x) / 2,
            (WINDOW_HEIGHT - game_over_text_characters_size) / 4
        )
    );

    std::string music_filename = "Battle in the Stars.ogg";
    fs::path music_path = fs::current_path() / "resources" / "sounds" / music_filename;
    sf::Music music;
    if(!music.openFromFile(music_path.string())) {
#ifdef GAME_DEBUG
        std::cout << "Error loading music" << std::endl;
#endif
        return -1;
    }

    music.setLoop(true);
    music.setVolume(MUSIC_VOLUME);

    Player* player = new Player(40.f, 40.f);

    sf::Text points_text;
    points_text.setFont(font);
    points_text.setString("Points: " + std::to_string(player->points()));
    points_text.setCharacterSize(12);
    points_text.setPosition(sf::Vector2f(0.f, 0.f));

    // TODO: change health color to green / yellow / red
    sf::Text players_health_text;
    players_health_text.setFont(font);
    players_health_text.setString("Health: " + std::to_string(player->health()));
    players_health_text.setCharacterSize(12);
    players_health_text.setPosition(sf::Vector2f(0.f, 15.f));

    sf::Clock enemies_timer;
    sf::Clock bullets_timer;

    Scene* scene = new Scene(player);

    if(MUSIC)
        music.play();

    bool game_is_playing = false;
    bool game_is_over = false;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            
            if(game_is_playing) {
                scene->handle_player(event);
            } 
            if(game_is_over) {
                delete scene;
                if(event.key.code == sf::Keyboard::Space) {
                    game_is_playing = true;
                    game_is_over = false;
                    player->set_points(0);
                    player->set_health(60);
                    scene = new Scene(player);
                    enemies_timer.restart();
                    bullets_timer.restart();
                    points_text.setCharacterSize(12);
                    points_text.setPosition(sf::Vector2f(0.f, 0.f));
                }
            } 
            if(!game_is_over && !game_is_playing) {
                if(event.key.code == sf::Keyboard::Space)
                    game_is_playing = true;

                if(event.key.code == sf::Keyboard::Escape) {
                    game_is_playing = false;
                }
            }


        }

        window.clear();

        if(game_is_playing) { 
            if(player->health() <= 0) {
                game_is_over = true;
                game_is_playing = false;
            }
            
            if(!game_is_over) {
                scene->update_scene(event, bullets_timer, enemies_timer);
                bool destroy_sound = false;

                points_text.setString("Points: "  + std::to_string(player->points()));
                window.draw(points_text);

                players_health_text.setString("Health: " + std::to_string(player->health()));
                window.draw(players_health_text);

                // Draw stars
                for(auto star : scene->stars()) {
                    window.draw(star->sprite());
                }
        
                // Draw effects
                for(auto effect : scene->effects()) {
                    window.draw(effect->sprite());
                    destroy_sound = true;
                }
        
                // Draw player
                window.draw(scene->player()->sprite());
        
                // Draw player bullets
                for(auto bullet : scene->bullets()) {
                    window.draw(bullet->sprite());
                }

                for(auto bullet : scene->enemies_bullets()) {
                    window.draw(bullet->sprite());
                }
        
                // Draw enemies
                for(auto enemy : scene->enemies()) {
                    window.draw(enemy->sprite());
                }
            }   
        } 

        if (game_is_over) {
            // DRAW GAME OVER
            window.draw(game_over_text);
            points_text.setCharacterSize(24);
            points_text.setPosition(
                sf::Vector2f(
                    (WINDOW_WIDTH - press_start_text.getLocalBounds().getSize().x) / 2,
                    (WINDOW_HEIGHT - start_text_charachers_size) / 2
               )
            );
            window.draw(points_text);
            press_start_text.setPosition(
                sf::Vector2f(
                     (WINDOW_WIDTH - press_start_text.getLocalBounds().getSize().x) / 2,
                     (WINDOW_HEIGHT - start_text_charachers_size) / 2 + 50.f
                )
            ); 
            window.draw(press_start_text);
        } 

        if(!game_is_over && !game_is_playing) {
            // DRAW MAIN MENU SCREEN
            window.draw(game_title_text);
            press_start_text.setPosition(
                sf::Vector2f(
                     (WINDOW_WIDTH - press_start_text.getLocalBounds().getSize().x) / 2,
                     (WINDOW_HEIGHT - start_text_charachers_size) / 2
                )
            ); 
            window.draw(press_start_text);
        }
        window.display();
    }

    return 0;
}