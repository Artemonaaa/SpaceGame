#pragma once

#include <random>

#include <Maths.h>

inline auto GRandomEngine = std::mt19937(std::random_device()());

inline float RandomFloat() {
	auto Distribution = std::uniform_real_distribution<float>(0.0F, 1.0F);
	return Distribution(GRandomEngine);
}

template <typename T>
inline T RandomFromTo(T From, T To) {
	auto Distribution = std::uniform_real_distribution<T>(From, To);
	return Distribution(GRandomEngine);
}

inline sf::Vector2f RandomPointInCircle2f() {
	while (true) {
		auto RandomVector = sf::Vector2f(RandomFromTo<float>(-1.0F, 1.0F), RandomFromTo<float>(-1.0F, 1.0F));
		if (GetLength(RandomVector) <= 1.0f) {
			return RandomVector;
		}	
	}
}
