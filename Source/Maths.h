#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

constexpr float Pi = 3.141592653589793238462643383279502884197F;

inline auto GetLength(sf::Vector2f Vector) -> float {
	return sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
}

inline auto GetNormalized(sf::Vector2f Vector) -> sf::Vector2f {
	float Length = GetLength(Vector);
	if (Length == 0.0f) {
		return Vector;
	}
	return Vector / Length;
}	
