#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <filesystem>

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "star.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "destroy_effect.hpp"

namespace fs = std::filesystem;


// TODO: remove sound buffer and destroy sound from this class
class Scene
{
private:
    fs::path m_texture_file;
    const std::string c_destroy_effect_sound = (fs::current_path() / "resources" / "sounds" / "Hit 1.mp3").string();

    Player* m_player;

    const size_t stars_count = 200;
    std::vector<Star*> m_stars;
    
    std::vector<Bullet*> m_bullets;
    std::vector<Bullet*> m_enemies_bullets;

    const size_t m_enemies_num = 5;
    std::vector<Enemy*> m_enemies;

    std::vector<DestroyEffect*> m_effects;

    sf::SoundBuffer m_destroy_effect_buffer;
    sf::Sound m_destroy_sound;

    std::vector<sf::Sound*> m_sounds;
private:
    void _create_stars();    
    bool _check_collision(const Bullet* b, const Enemy* e);
    bool _check_collision_player(const Bullet* b);
    void _handle_enemies(sf::Clock& enemies_timer);
    void _handle_bullets();
    void _handle_effects();
    void _delete_sounds();
public:
    Scene();
    Scene(Player* player);
    ~Scene();
    
    const Player* player() const { return m_player; }
    const std::vector<Star*>& stars() const { return m_stars; }
    const std::vector<Bullet*>& bullets() const { return m_bullets; }
    const std::vector<Bullet*>& enemies_bullets() { return m_enemies_bullets; }
    const std::vector<Enemy*>& enemies() const { return m_enemies; }
    const std::vector<DestroyEffect*>& effects() const { return m_effects; }
    std::vector<sf::Sound*> sounds() { return m_sounds; }
    sf::Sound destroy_sound() { return m_destroy_sound; }
    
    void handle_player(const sf::Event& e);
    void update_scene(const sf::Event& e, sf::Clock& bullets_timer, sf::Clock& enemies_timer);
};
#endif // __SCENE_H__