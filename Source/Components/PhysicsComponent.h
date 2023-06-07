#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <vector>

struct TCollisionEvent {
    entt::entity Other = {};
    bool* ShouldRespond = nullptr;
};

struct TPairCollisionEvent {
    entt::entity First = {};
    entt::entity Second = {};
    bool ShouldRespond = false;
};

struct TPhysicsComponent {
    sf::Vector2f Velocity = sf::Vector2f();
    float Radius = 0;
    std::vector<TCollisionEvent> CollisionEvents;
};
