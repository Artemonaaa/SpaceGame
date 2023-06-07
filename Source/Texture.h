#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

struct TTextures {
	TTextures() {
		SpaceShip.loadFromFile("../../../Texture/ship_1.png");
		Bullet.loadFromFile("../../../Texture/Bullet.png");
		Asteroid.loadFromFile("../../../Texture/Asteroid1.png");
	}

	sf::Texture SpaceShip;
	sf::Texture Bullet;
	sf::Texture Asteroid;
};

inline std::optional<TTextures> GTextures;