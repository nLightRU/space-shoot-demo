#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <filesystem>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Star.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "DestroyEffect.hpp"

namespace fs = std::filesystem;

class Scene
{
private:
    Player* m_player;

    const size_t stars_count = 200;
    std::vector<Star*> m_stars;
    
    std::vector<Bullet*> m_bullets;

    const size_t m_enemies_num = 5;
    std::vector<Enemy*> m_enemies;

    std::vector<DestroyEffect*> m_effects;

    fs::path m_texture_file;

private:
    void create_stars();    
    bool check_collision(const Bullet* b, const Enemy* e);
    void handle_bullets();
    void handle_effects();
public:
    Scene();
    Scene(Player* player);
    ~Scene();
    
    const Player* player() const {return m_player; }
    const std::vector<Star*>& stars() const {return m_stars; }
    const std::vector<Bullet*>& bullets() const {return m_bullets; }
    const std::vector<Enemy*>& enemies() const { return m_enemies; }
    const std::vector<DestroyEffect*>& effects() const { return m_effects; }
    
    void add_object();
    void handle_player(const sf::Event& e);
    void update_scene(const sf::Event& e, sf::Clock& bullets_timer, sf::Clock& enemies_timer);
};

#endif // __SCENE_H__