#include <SFML/Graphics.hpp>

#include "SpaceShipSystem.h"

#include "Components/TransformComponent.h"
#include "Components/SpaceShipComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PhysicsComponent.h"
#include <Components/BulletComponent.h>

#include "Maths.h"
#include "Texture.h"

auto CreateEntityBullet(entt::registry& Registry, sf::Vector2f Position, float Rotation, sf::Vector2f Velocity) -> entt::entity {
	auto Entity = Registry.create();

	Registry.emplace<TSpriteComponent>(Entity, GetCentered(sf::Sprite(GTextures->Bullet)));
	Registry.emplace<TTransformComponent>(Entity, Position, Rotation);
	Registry.emplace<TPhysicsComponent>(Entity, Velocity, 8.0f);
	Registry.emplace<TBulletComponent>(Entity);

	return Entity;
}

auto SpaceShipSystemUpdate(entt::registry& Registry, sf::RenderWindow& Window, float DeltaTime) -> void {
	auto View = Registry.view<TSpaceShipComponent, TTransformComponent, TPhysicsComponent>();

	View.each([DeltaTime, &Window, &Registry](TSpaceShipComponent& SpaceShipComponent,TTransformComponent& TransformComponent, TPhysicsComponent& PhysicsComponent) {
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
		PhysicsComponent.Velocity = Offset * Speed;

		sf::Vector2f MousePosition = sf::Vector2f(sf::Mouse::getPosition(Window));
		sf::Vector2f ToMouse = MousePosition - TransformComponent.Position;

		TransformComponent.Rotation = GetAngle(ToMouse) + Pi / 2;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && SpaceShipComponent.BulletTimer.getElapsedTime().asSeconds() > 0.25F) {
			CreateEntityBullet(Registry, TransformComponent.Position, TransformComponent.Rotation, GetNormalized(ToMouse) * Speed);
			SpaceShipComponent.BulletTimer.restart();
		}
	});
}
