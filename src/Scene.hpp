#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Star.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

class Scene
{
private:
    Player* m_player;

    const size_t stars_count = 200;
    std::vector<Star*> m_stars;
    
    std::vector<Bullet*> m_bullets;

    const size_t m_enemies_num = 5;
    std::vector<Enemy*> m_enemies;

private:
    void create_stars();    
    bool check_collision(const Bullet* b, const Enemy* e);
    void handle_bullets();
public:
    Scene();
    Scene(Player* player);
    ~Scene();
    
    const Player* player() const {return m_player; }
    const std::vector<Star*>& stars() const {return m_stars; }
    const std::vector<Bullet*>& bullets() const {return m_bullets; }
    const std::vector<Enemy*>& enemies() const { return m_enemies; }
    
    void add_object();
    void handle_player(const sf::Event& e);
    void update_scene(const sf::Event& e, sf::Clock& bullets_timer, sf::Clock& enemies_timer);
};

#endif // __SCENE_H__