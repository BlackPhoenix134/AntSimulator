#pragma once
#include "Settings.hpp"
#include <iostream>

class WorldGridEntry {
	virtual void poly();
};


enum class PheromoneType : uint8_t {
	AntPrecense, ToFood
};

class Pheromone: public WorldGridEntry {
public:
	Pheromone();
	Pheromone(PheromoneType type);
	PheromoneType type = PheromoneType::AntPrecense;
	float lifeTime = Settings::PHEROMONE_LIFETIME;
};

class Wall: public WorldGridEntry {
};

class Food : public WorldGridEntry {
};
