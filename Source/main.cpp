#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "System/SpriteSystem.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Texture.h"

auto CreateEntitySpaceShip(entt::registry& Registry) -> entt::entity {
    auto Entity = Registry.create();
   
    Registry.emplace<TSpriteComponent>(Entity, sf::Sprite(GTextures->SpaceShip));
    Registry.emplace<TTransformComponent>(Entity, sf::Vector2f(100.0f, 100.0f));

    return Entity;
}

int main() {
    GTextures.emplace();

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Space Game");
    entt::registry Registry;

    CreateEntitySpaceShip(Registry);

    while (Window.isOpen()) {
        sf::Event Event;
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            }
        }   

        Window.clear();
        SpriteSystemUpdate(Registry, Window);
        Window.display();
    }

    GTextures.reset();
    return 0;
}