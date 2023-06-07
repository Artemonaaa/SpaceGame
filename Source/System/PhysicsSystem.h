#pragma once

#include <entt/entt.hpp>
#include <vector>

#include "Components/PhysicsComponent.h"

class TPhysicsSystem {
public:
	auto Update(entt::registry& Registry, float DeltaTime) -> void;

public:
	std::vector<TPairCollisionEvent> PairCollisionEvents;
};
