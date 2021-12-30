#pragma once
#include "aspch.hpp"
#include "entt.hpp"
#include "mathfu/glsl_mappings.h"


constexpr short gridSize = 200;
constexpr short cellSize = 25;

struct Context {
	Camera2D* camera2D;
	SpatialHash spatialHash = SpatialHash(50);
	Grid<uint8_t> worldWalls = Grid<uint8_t>(gridSize, gridSize, cellSize,
		mathfu::vec2(-gridSize / 2 * cellSize, -gridSize / 2 * cellSize));
	GridMulti<entt::entity> worldGrid = GridMulti<entt::entity>(gridSize, gridSize, cellSize,
		mathfu::vec2(-gridSize / 2 * cellSize, -gridSize / 2 * cellSize));
	entt::registry registry;
	float deltaTime;
};