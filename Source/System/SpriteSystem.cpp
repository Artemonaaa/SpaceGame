#include "SpriteSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"

auto SpriteSystemUpdate(entt::registry& Registry, sf::RenderWindow& Window) -> void {
    auto View = Registry.view<TTransformComponent, TSpriteComponent>();

    View.each([&Window](TTransformComponent& TransformComponent, TSpriteComponent& SpriteComponent) {
        SpriteComponent.Sprite.setPosition(TransformComponent.Position);
        Window.draw(SpriteComponent.Sprite);
    });
}