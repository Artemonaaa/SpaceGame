#include "BulletSystem.h"

#include "Components/BulletComponent.h"

auto BulletSystemUpdate(entt::registry& Registry) -> void {
	auto View = Registry.view<TBulletComponent>();

	View.each([&Registry](entt::entity Entity, TBulletComponent& BulletComponent) {
		if (BulletComponent.LifeTime.getElapsedTime().asSeconds() > 1.0f) {
			Registry.destroy(Entity);
		}
	});
}		
