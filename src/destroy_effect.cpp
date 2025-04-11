#include <string>
#include <filesystem>

#include <SFML/Graphics/Rect.hpp>

#include "destroy_effect.hpp"

DestroyEffect::DestroyEffect(float x, float y, const std::string& texture_file) : m_x(x), m_y(y), m_current_texture(0)
{
    m_animation_textures.reserve(5);
    std::vector<sf::IntRect> rects = {
        sf::IntRect(972, 113, 20, 20),
        sf::IntRect(954, 111, 20, 20),
        sf::IntRect(933, 109, 20, 20),
        sf::IntRect(908, 108, 20, 20),
        sf::IntRect(883, 106, 20, 20)
    };

    for(size_t i = 0; i < rects.size(); ++i) {
        m_animation_textures.emplace_back(new sf::Texture());
    }

    for(size_t i = 0; i < rects.size(); ++i) {
        m_animation_textures[i]->loadFromFile(texture_file, rects[i]);
    }

    m_sprite.setTexture(*m_animation_textures[m_current_texture]);
    m_sprite.setPosition(m_x, m_y);
}


void DestroyEffect::set_next_sprite()
{
    if(m_clock.getElapsedTime().asMilliseconds() > m_delta) {
        m_current_texture += 1;
        if(m_current_texture < m_animation_textures.size()) {
            m_sprite.setTexture(*m_animation_textures[m_current_texture]);
        }
        m_clock.restart();
    }
}

bool DestroyEffect::has_next_sprite() {
    return m_current_texture < m_animation_textures.size();
}
