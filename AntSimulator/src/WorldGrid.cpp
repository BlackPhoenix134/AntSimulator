#include "WorldGrid.hpp"


WorldGridEntry* WorldGrid::get(const mathfu::vec2i& cellIdx)
{
	return grid.get(cellIdx)->get();
}

mathfu::vec2i WorldGrid::toCellIdx(const mathfu::vec2& worldPos) const
{
	return grid.toCellIdx(worldPos);
}

mathfu::vec2 WorldGrid::toWorldPos(const mathfu::vec2i& cellIdx) const
{
	return grid.toWorldPos(cellIdx);
}

void WorldGrid::set(const mathfu::vec2i& cellIdx, WorldGridEntry entry)
{
	grid.set(cellIdx, std::unique_ptr<WorldGridEntry>(new WorldGridEntry(entry)));
}

void WorldGrid::remove(const mathfu::vec2i& cellIdx)
{
	grid.set(cellIdx, nullptr);
}

bool WorldGrid::has(const mathfu::vec2i& cellIdx)
{
	return grid.get(cellIdx) != nullptr;
}

short WorldGrid::getSizeX()
{
	return grid.getSizeX();
}

short WorldGrid::getSizeY()
{
	return grid.getSizeY();
}

short WorldGrid::getCellSize()
{
	return grid.getCellSize();
}
