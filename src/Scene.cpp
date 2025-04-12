#ifdef GAME_DEBUG
#include <iostream>
#endif
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include <SFML/Window/Event.hpp>
#include <SFML/Audio/Sound.hpp>

#include "config.hpp"
#include "scene.hpp"
#include "star.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

void Scene::_create_stars()
{
    srand(time({}));
    m_stars.reserve(200);
    for(size_t i = 0; i < this->stars_count; ++i) {
        float star_x = 20 + rand() % 640;
        float star_y = rand() % 400;
        m_stars.emplace_back(new Star(star_x, star_y)); 
    }
}

bool Scene::_check_collision(const Bullet* b, const Enemy* e) {
    if(b->x() > e->x() && b->x() < (e->x() + e->w())) {
        if(b->y() > e->y() && b->y() < (e->y() + e->h())) {
            return true;
        }
    }
    return false;
}

bool Scene::_check_collision_player(const Bullet* b) {
    if(b->x() > m_player->x() && b->x() < (m_player->x() + m_player->w())) {
        if(b->y() > m_player->y() && b->y() < (m_player->y() + m_player->h())) {
            return true;
        }
    }
    return false;
}

// TODO: check can we make private inline funcion for adding effect inline void Scene::_add_destroy_effect();
// TODO: check can we rewrite loop in (for auto bullet : bullets) form
// TODO: move sounds to _handle_effect_function
void Scene::_handle_bullets()
{
    // Moving player bullets and checking collisions
#ifdef GAME_DEBUG
    std::cout << "Player bullets: " << m_bullets.size() << std::endl;
#endif
    for(size_t i = 0; i < m_bullets.size(); ++i) {
        bool collision = false;
        m_bullets[i]->move();
        for(size_t j = 0; j < m_enemies.size(); ++j) {
            if(_check_collision(m_bullets[i], m_enemies[j])) {
                m_bullets.erase(m_bullets.begin() + i);
                m_effects.push_back(
                    new DestroyEffect(m_enemies[j]->x(), m_enemies[j]->y(), m_texture_file.string())
                );
                m_sounds.push_back(new sf::Sound(m_destroy_effect_buffer));
                m_sounds.back()->setVolume(EFFECT_VOLUME);
                m_sounds.back()->play();
                m_enemies.erase(m_enemies.begin() + j);
                m_player->add_points(50);
                collision = true;
                continue;
            }
        }
        if(collision) {
            continue;
        } else if(m_bullets[i]->y() < 0.f ) {
            m_bullets.erase(m_bullets.begin() + i);
        }
    }
    
    // Moving enemies bullets and checking collision
#ifdef GAME_DEBUG
    std::cout << "Enemies bullets: " << m_enemies_bullets.size() << std::endl;
#endif
    for(size_t i = 0; i < m_enemies_bullets.size(); ++i) {
        bool collision = _check_collision_player(m_enemies_bullets[i]);
        m_enemies_bullets[i]->move();
        if(collision) {
            // TODO: add damage from bullet after damage is added to the Bullet class
            m_player->apply_damage(20.f);
            m_enemies_bullets.erase(m_enemies_bullets.begin() + i);
        } else if (m_enemies_bullets[i]->y() > WINDOW_HEIGHT) {
            m_enemies_bullets.erase(m_enemies_bullets.begin() + i);
        }
    }
}

void Scene::_handle_effects() {
    for(size_t i = 0; i < m_effects.size(); ++i) {
        if(m_effects[i]->has_next_sprite()) {
            m_effects[i]->set_next_sprite();
        } else { 
            m_effects.erase(m_effects.begin() + i);
        }
    }
}

void Scene::_delete_sounds() {
    for(size_t i = 0; i < m_sounds.size(); ++i) {
        if(m_sounds.at(i)->getStatus() == sf::SoundSource::Status::Stopped) {
            m_sounds.erase(m_sounds.begin() + i);
        }
    }
}

void Scene::_handle_enemies(sf::Clock& enemies_timer)
{
    // Adds new enemy if need
    if(enemies_timer.getElapsedTime().asSeconds() > 2.f && m_enemies.size() < m_enemies_num ) {
        float x = rand() % 500;
        float y = rand() % 100;
        m_enemies.push_back(new Enemy(x, y, 40.f, 30.f));
        enemies_timer.restart();
    }

    for(auto enemy : m_enemies) {
        if(enemy->new_bullet()) {
            m_enemies_bullets.push_back(
                new Bullet(enemy->x(), enemy->y() + 4.f, false)
            );
        }
    }
    // TODO: enemies movement
}



Scene::Scene() {

}

Scene::Scene(Player *player) : 
m_player(player),
m_stars(),
m_enemies(),
m_effects(),
m_destroy_effect_buffer(),
m_destroy_sound(),
m_sounds()
{
    _create_stars();
    std::string texture_sheet_filename = "M484VerticalShmupSet1.png";
    m_texture_file = fs::current_path().append("resources").append("textures").append(texture_sheet_filename);    
    if(!m_destroy_effect_buffer.loadFromFile(c_destroy_effect_sound)) {
#ifdef GAME_DEBUG
    std::cout << "Error loading sound buffer" << std::endl;
#endif
    }
    m_destroy_sound.setBuffer(m_destroy_effect_buffer);
    m_destroy_sound.setVolume(EFFECT_VOLUME);
}

Scene::~Scene()
{

}

void Scene::handle_player(const sf::Event& e)
{
#ifdef GAME_DEBUG
    std::cout << "KEY: " << e.key.code << std::endl;
#endif
    if(e.key.code == sf::Keyboard::W && m_player->y() > 32.f) {
        m_player->move_up();
    } else if (e.key.code == sf::Keyboard::A && m_player->x() > 32.f) {
        m_player->move_left();
    } else if (e.key.code == sf::Keyboard::S && m_player->y() < WINDOW_HEIGHT - 32.f) {
        m_player->move_down();
    } else if (e.key.code == sf::Keyboard::D && m_player->x() < WINDOW_WIDTH - 32.f) {
        m_player->move_right();
    }
}

// TODO: remove enemies_timer from main loop and make it inside Scene class
void Scene::update_scene(const sf::Event& e, sf::Clock& bullets_timer, sf::Clock& enemies_timer)
{
    //Moves stars
    for(auto star : m_stars) {
        star->move();
    }

    // Creates new bullets
    if(bullets_timer.getElapsedTime().asMilliseconds() > 500.f) {
        m_bullets.push_back(new Bullet(m_player->x() + 17.f, m_player->y() - 20.f));
        bullets_timer.restart();
    }

    _handle_enemies(enemies_timer);

    // Checks bullets collisions with enemies
    // Creates effects
    _handle_bullets();

    //Effects
    _handle_effects();

    _delete_sounds();
}
