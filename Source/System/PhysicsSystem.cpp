#include "PhysicsSystem.h"

#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"
#include "Maths.h"

auto PhysicsSystemUpdate(entt::registry& Registry, float DeltaTime) -> void {
	auto View = Registry.view<TPhysicsComponent, TTransformComponent>();

    View.each([DeltaTime](TPhysicsComponent& PhysicsComponent, TTransformComponent& TransformComponent) {
		TransformComponent.Position += PhysicsComponent.Velocity * DeltaTime;
    });
}
