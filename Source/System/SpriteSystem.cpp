#include "SpriteSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"

#include "Texture.h"
#include "Maths.h"

auto SpriteSystemUpdate(entt::registry& Registry, sf::RenderWindow& Window) -> void {
    auto View = Registry.view<const TTransformComponent, TSpriteComponent>();

    View.each([&Window](const TTransformComponent& TransformComponent, TSpriteComponent& SpriteComponent) {
        SpriteComponent.Sprite.setPosition(TransformComponent.Position);
        SpriteComponent.Sprite.setRotation(TransformComponent.Rotation / Pi * 180.0F);

        Window.draw(SpriteComponent.Sprite);
    });
}