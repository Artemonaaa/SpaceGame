#pragma once

#include <SFML/Graphics.hpp>

struct TPhysicComponent {
    sf::Vector2f Direction = sf::Vector2f();
    sf::Vector2f Velocity = sf::Vector2f();
};