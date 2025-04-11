#ifndef __DESTROYEFFECT_H__
#define __DESTROYEFFECT_H__

#include <string>
#include <vector>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

// TO DO
// make class BaseEffect with methods: next_sprite, has_next_sprite
// or make interface Animated
class DestroyEffect {
private:
    float m_x, m_y;
    float m_w, m_h;
    const float m_delta = 25.f;
    size_t m_current_texture;
    sf::Clock m_clock;
    std::vector<sf::Texture*> m_animation_textures;
    sf::Sprite m_sprite;
    sf::SoundBuffer m_sound_buffer;
    sf::Sound m_sound; 
public:
    DestroyEffect(float x, float y, const std::string& texture_file);
    const sf::Sprite& sprite() const { return m_sprite; }
    sf::Sound sound() const { return m_sound; }
    void set_next_sprite();
    bool has_next_sprite();
};
#endif // __EFFECT_H__