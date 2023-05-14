#include <SFML/Graphics.hpp>

#include "SpaceShipSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpaceShipComponent.h"
#include "Components/SpriteComponent.h"
#include "Maths.h"

auto SpaceShipSystemUpdate(entt::registry& Registry, sf::RenderWindow& Window, float DeltaTime) -> void {
	auto View = Registry.view<TSpaceShipComponent, TTransformComponent, TSpriteComponent>();

	View.each([DeltaTime, &Window](TTransformComponent& TransformComponent, TSpriteComponent& SpriteComponent) {
		sf::Vector2f Offset;
		float Speed = 500.0F;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Offset.x += -1.0F;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Offset.x += 1.0F;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			Offset.y += -1.0F;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			Offset.y += 1.0F;
		}
		Offset = GetNormalized(Offset);
		TransformComponent.Position += Offset * Speed * DeltaTime;

		sf::Vector2f MousePosition = sf::Vector2f(sf::Mouse::getPosition(Window));
		sf::Vector2f ToMouse = MousePosition - SpriteComponent.Sprite.getPosition();

		SpriteComponent.Sprite.setRotation(GetAngle(ToMouse) + 90.0f);
	});
}
