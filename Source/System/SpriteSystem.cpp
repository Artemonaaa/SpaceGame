#include "SpriteSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Texture.h"

auto SpriteSystemUpdate(entt::registry& Registry, sf::RenderWindow& Window) -> void {
    auto View = Registry.view<TTransformComponent, TSpriteComponent>();

    View.each([&Window](TTransformComponent& TransformComponent, TSpriteComponent& SpriteComponent) {
        SpriteComponent.Sprite.setPosition(TransformComponent.Position);
        SpriteComponent.Sprite.setOrigin(sf::Vector2f(GTextures->SpaceShip.getSize()) / 2.0f);
        Window.draw(SpriteComponent.Sprite);
    });
}