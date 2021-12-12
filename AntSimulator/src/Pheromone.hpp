#pragma once
#include "Settings.hpp"
#include <iostream>

enum class PheromoneType : uint8_t {
	None, AntPrecense, ToFood
};

class Pheromone {
public:
	PheromoneType type = PheromoneType::None;
	float lifeTime = Settings::PHEROMONE_LIFETIME;
private:
};