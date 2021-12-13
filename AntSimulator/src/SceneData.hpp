#pragma once
#include "Settings.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

class WorldGridEntry {
public:
	virtual Texture2D getTexture() = 0;
	virtual Color getColor();
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

	Texture2D getTexture();
	Color getColor();
};

class Wall: public WorldGridEntry {
public:
	Texture2D getTexture();
};

class Food : public WorldGridEntry {
public:
	Texture2D getTexture();
};
