#include "PhysicsSystem.h"

#include "Components/PhysicsComponent.h"
#include "Components/TransformComponent.h"

#include "Maths.h"

auto TPhysicsSystem::Update(entt::registry& Registry, float DeltaTime) -> void {
	auto View = Registry.view<TPhysicsComponent, TTransformComponent>();

	for (auto& PairCollisionEvent : PairCollisionEvents) {
		if (!PairCollisionEvent.ShouldRespond) {
			continue;
		}

		auto& FirstTransformComponent = View.get<TTransformComponent>(PairCollisionEvent.First);
		auto& FirstPhysicsComponent = View.get<TPhysicsComponent>(PairCollisionEvent.First);

		auto& SecondTransformComponent = View.get<TTransformComponent>(PairCollisionEvent.Second);
		auto& SecondPhysicsComponent = View.get<TPhysicsComponent>(PairCollisionEvent.Second);

		float Distance = GetLength(FirstTransformComponent.Position - SecondTransformComponent.Position);
		float Overlap = 0.5f * (Distance - FirstPhysicsComponent.Radius - SecondPhysicsComponent.Radius);

		sf::Vector2f ToSecond = SecondTransformComponent.Position - FirstTransformComponent.Position;

		FirstTransformComponent.Position += GetNormalized(ToSecond) * Overlap;
		SecondTransformComponent.Position += -GetNormalized(ToSecond) * Overlap;

		Distance = GetLength(FirstTransformComponent.Position - SecondTransformComponent.Position);

		sf::Vector2f NormalizedVector = GetNormalized(FirstTransformComponent.Position - SecondTransformComponent.Position);

		auto TangentVector = sf::Vector2f(-NormalizedVector.y, NormalizedVector.x);

		auto DotProductTangent = sf::Vector2f(
			FirstPhysicsComponent.Velocity.x * TangentVector.x + FirstPhysicsComponent.Velocity.y * TangentVector.y,
			SecondPhysicsComponent.Velocity.x * TangentVector.x + SecondPhysicsComponent.Velocity.y * TangentVector.y
		);

		auto DotProductNormalized = sf::Vector2f(
			FirstPhysicsComponent.Velocity.x * NormalizedVector.x + FirstPhysicsComponent.Velocity.y * NormalizedVector.y,
			SecondPhysicsComponent.Velocity.x * NormalizedVector.x + SecondPhysicsComponent.Velocity.y * NormalizedVector.y
		);

		auto Mass = sf::Vector2f(
			 DotProductNormalized.y,
			 DotProductNormalized.x
		);

		FirstPhysicsComponent.Velocity.x = TangentVector.x * DotProductTangent.x + NormalizedVector.x * Mass.x;
		FirstPhysicsComponent.Velocity.y = TangentVector.y * DotProductTangent.x + NormalizedVector.y * Mass.x;
		SecondPhysicsComponent.Velocity.x = TangentVector.x * DotProductTangent.y + NormalizedVector.x * Mass.y;
		SecondPhysicsComponent.Velocity.y = TangentVector.y * DotProductTangent.y + NormalizedVector.y * Mass.y;
	}
	PairCollisionEvents.clear();

	auto End = View.end();
	for (auto I = View.begin(); I != End; ++I) {
		auto& FirstTransformComponent = View.get<TTransformComponent>(*I);
		auto& FirstPhysicsComponent = View.get<TPhysicsComponent>(*I);

		FirstTransformComponent.Position += FirstPhysicsComponent.Velocity * DeltaTime;

		auto J = I;
		++J;
		for (; J != End; ++J) {
			auto& SecondTransformComponent = View.get<TTransformComponent>(*J);
			auto& SecondPhysicsComponent = View.get<TPhysicsComponent>(*J);

			if (GetLength(FirstTransformComponent.Position - SecondTransformComponent.Position) <= FirstPhysicsComponent.Radius + SecondPhysicsComponent.Radius) {
				PairCollisionEvents.emplace_back(TPairCollisionEvent {
					.First = *I,
					.Second = *J,
				});
			}
		}

		FirstPhysicsComponent.CollisionEvents.clear();
	}

	for (auto& PairCollisionEvent : PairCollisionEvents) {
		auto& FirstPhysicsComponent = View.get<TPhysicsComponent>(PairCollisionEvent.First);
		auto& SecondPhysicsComponent = View.get<TPhysicsComponent>(PairCollisionEvent.Second);

		FirstPhysicsComponent.CollisionEvents.push_back(TCollisionEvent {
			.Other = PairCollisionEvent.Second,
			.ShouldRespond = &PairCollisionEvent.ShouldRespond,
		});

		SecondPhysicsComponent.CollisionEvents.push_back(TCollisionEvent {
			.Other = PairCollisionEvent.First,
			.ShouldRespond = &PairCollisionEvent.ShouldRespond,
		});
	}
}
