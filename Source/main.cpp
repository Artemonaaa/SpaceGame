#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include <format>

#include "System/SpriteSystem.h"
#include "System/PhysicsSystem.h"
#include "System/SpaceShipSystem.h"
#include "System/BulletSystem.h"
#include "System/AsteroidSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpaceShipComponent.h"
#include "Components/AsteroidComponent.h"

#include "Texture.h"
#include "Random.h"


auto CreateEntitySpaceShip(entt::registry& Registry) -> entt::entity {
    auto Entity = Registry.create();

    Registry.emplace<TSpriteComponent>(Entity, GetCentered(sf::Sprite(GTextures->SpaceShip)));
    Registry.emplace<TTransformComponent>(Entity, sf::Vector2f(400.0F, 300.0F));
    Registry.emplace<TPhysicsComponent>(Entity, sf::Vector2f(0.0F, 0.0F));
    Registry.emplace<TSpaceShipComponent>(Entity);

    return Entity;
}

auto OnPhysicsComponentDestroy(entt::registry& Registry, entt::entity Entity) -> void {
    for (auto& CollisionEvent : Registry.get<TPhysicsComponent>(Entity).CollisionEvents) {
        *CollisionEvent.ShouldRespond = false;
    }
}

int main() {
    GTextures.emplace();    

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Space Game");
    entt::registry Registry;

    sf::Clock DeltaClock;

    Registry.on_destroy<TPhysicsComponent>().connect<OnPhysicsComponentDestroy>();

    CreateEntitySpaceShip(Registry);
    auto AsteroidSystem = TAsteroidSystem();
    auto PhysicsSystem = TPhysicsSystem();

    while (Window.isOpen()) {
        sf::Event Event;
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            }
        }   

        float DeltaTime = DeltaClock.restart().asSeconds();

        PhysicsSystem.Update(Registry, DeltaTime);
        SpaceShipSystemUpdate(Registry, Window, DeltaTime);
        BulletSystemUpdate(Registry);
        AsteroidSystem.Update(Registry, Window);

        Window.clear();
        SpriteSystemUpdate(Registry, Window);
        Window.display();
    }

    GTextures.reset();
    return 0;
}