#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class TAsteroidSystem {
public:
    auto Update(entt::registry& Registry, sf::RenderWindow& Window) -> void;
private:
    sf::Clock AsteroidSpawnTimer;
};
