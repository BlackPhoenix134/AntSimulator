#pragma once
#include "aspch.hpp"
#include "entt.hpp"


struct Context {
	SpatialHash spatialHash = SpatialHash(50);
	Grid<bool> worldWalls = Grid<bool>(500, 500, 25);
	entt::registry registry;
	float deltaTime;
};