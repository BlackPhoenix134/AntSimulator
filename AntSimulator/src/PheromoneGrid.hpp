#pragma once

#include "Pheromone.hpp"
#include "Grid.hpp"

namespace PheromoneGrid {
	void set(const mathfu::vec2i& cellIdx, PheromoneType type, Grid<Pheromone>& grid);
}