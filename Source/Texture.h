#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

struct TTextures {
	TTextures() {
		SpaceShip.loadFromFile("../../../Texture/ship_1.png");
	}

	sf::Texture SpaceShip;
};

std::optional<TTextures> GTextures;