#pragma once

#include "SceneData.hpp"
#include "Grid.hpp"

namespace PheromoneGrid {
	void set(const mathfu::vec2i& cellIdx, PheromoneType type, Grid<Pheromone>& grid);
}