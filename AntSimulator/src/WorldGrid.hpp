#pragma once

#include "SceneData.hpp"
#include "Grid.hpp"
#include "mathfu/glsl_mappings.h"
#include <memory>

constexpr int gridSize = 500;
constexpr int gridCellSize = 20;

class WorldGrid {
public:
	WorldGridEntry* get(const mathfu::vec2i& cellIdx);
	mathfu::vec2i toCellIdx(const mathfu::vec2& worldPos) const;
	mathfu::vec2 toWorldPos(const mathfu::vec2i& cellIdx) const;
	void set(const mathfu::vec2i& cellIdx, WorldGridEntry entry);
	bool has(const mathfu::vec2i& cellIdx);
	short getSizeX();
	short getSizeY();
	short getCellSize();
private:
	Grid<std::unique_ptr<WorldGridEntry>> grid =
		Grid<std::unique_ptr<WorldGridEntry>>(gridSize, gridSize, gridCellSize, mathfu::vec2(gridSize / 2 * gridCellSize));
};