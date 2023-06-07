#include "AsteroidSystem.h"

#include "Components/AsteroidComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpaceShipComponent.h"
#include "Components/BulletComponent.h"

#include "Texture.h"
#include "Random.h"

auto CreateEntityAsteroid(entt::registry& Registry, sf::Vector2f Position) -> entt::entity {
    auto Entity = Registry.create();

    Registry.emplace<TSpriteComponent>(Entity, GetCentered(sf::Sprite(GTextures->Asteroid)));
    Registry.emplace<TTransformComponent>(Entity, Position);
    Registry.emplace<TPhysicsComponent>(Entity, sf::Vector2f(RandomFromTo(-1.0F, 1.0F), RandomFromTo(-1.0F, 1.0F)) * 100.0F, 22.0F);
    Registry.emplace<TAsteroidComponent>(Entity);

    return Entity;
}

inline sf::Vector2f RandomAsteroidSpawn(sf::Vector2f PositionSpaceShip) {
    auto Normalized = GetNormalized(RandomPointInCircle2f());

    return sf::Vector2f(Normalized * 100.0F + Normalized * 200.0f * sqrtf(RandomFloat()) + PositionSpaceShip);
}


auto TAsteroidSystem::Update(entt::registry& Registry, sf::RenderWindow& Window) -> void {
    auto AsteroidView = Registry.view<TAsteroidComponent, TPhysicsComponent>();

    AsteroidView.each([&](entt::entity Entity, TAsteroidComponent& AsteroidComponent, TPhysicsComponent& PhysicsComponent) {
        for (auto& CollisionEvent : PhysicsComponent.CollisionEvents) {
            if (Registry.try_get<TAsteroidComponent>(CollisionEvent.Other) != nullptr) {
                *CollisionEvent.ShouldRespond = true;
            }
            if (Registry.try_get<TBulletComponent>(CollisionEvent.Other) != nullptr) {
                Registry.destroy(CollisionEvent.Other);
                Registry.destroy(Entity);
            }
        }
    });

    static bool WasPressed = false;

    if (!WasPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        CreateEntityAsteroid(Registry, sf::Vector2f(sf::Mouse::getPosition(Window)));
    }
    WasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    if (AsteroidSpawnTimer.getElapsedTime().asSeconds() <= 0.3F) {
        return;
    }
    AsteroidSpawnTimer.restart();

    auto SpaceShipView = Registry.view<const TSpaceShipComponent, const TTransformComponent>();
    SpaceShipView.each([&Registry](const TSpaceShipComponent& SpaceShipComponent, const TTransformComponent& TransformComponent) {
        CreateEntityAsteroid(Registry, RandomAsteroidSpawn(TransformComponent.Position));
    });

}
