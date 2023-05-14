#include <SFML/Graphics.hpp>

#include "SpaceShipSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpaceShipComponent.h"
#include "Maths.h"

auto SpaceShipSystemUpdate(entt::registry& Registry, float DeltaTime) -> void {
	auto View = Registry.view<TSpaceShipComponent, TTransformComponent>();

	View.each([DeltaTime](TTransformComponent& TransformComponent) {
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
	});
}
