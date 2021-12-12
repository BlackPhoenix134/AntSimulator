#include "PheromoneGrid.hpp"

namespace PheromoneGrid {
	void set(const mathfu::vec2i& cellIdx, PheromoneType type, Grid<Pheromone>& grid)
	{
		Pheromone* pheromone = grid.get(cellIdx);
		pheromone->type = type;
		pheromone->lifeTime = Settings::PHEROMONE_LIFETIME;
		//ToDo: priority override order, or no set at all, based on enum int values
	}
}