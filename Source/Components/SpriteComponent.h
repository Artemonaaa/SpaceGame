#pragma once

#include <SFML/Graphics.hpp>

struct TSpriteComponent {
    sf::Sprite Sprite = sf::Sprite();
};

inline auto GetCentered(sf::Sprite Sprite) -> sf::Sprite {
    Sprite.setOrigin(sf::Vector2f(Sprite.getTexture()->getSize()) / 2.0F);
    return Sprite;
}