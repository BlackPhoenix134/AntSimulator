#pragma once
#include "mathfu/glsl_mappings.h"
#include "mathfu/constants.h"


template <typename T>
class GridMulti
{
public:
	GridMulti(short sizeX, short sizeY, int cellSize) : GridMulti(sizeX, sizeY, cellSize, mathfu::kZeros2f) {
	}

	GridMulti(short sizeX, short sizeY, int cellSize, mathfu::vec2 offset) : sizeX(sizeX), sizeY(sizeY),
		cellSize(cellSize), offset(offset) {
		data.resize(sizeX * sizeY);
	}

	~GridMulti() {

	}

	mathfu::vec2i toCellIdx(const mathfu::vec2& worldPos) const
	{
		return mathfu::vec2i(floor((worldPos.x - offset.x) / cellSize), floor((worldPos.y - offset.y) / cellSize));
	}

	mathfu::vec2 toWorldPos(const mathfu::vec2i& cellIdx) const
	{
		return mathfu::vec2(cellIdx.x * cellSize + offset.x, cellIdx.y * cellSize + offset.y);
	}


	std::unordered_set<T>* get(const mathfu::vec2i& cellIdx) {
		return &data[sizeX * cellIdx.y + cellIdx.x];
	}

	void set(const mathfu::vec2i& cellIdx, const T& value)
	{
		auto* container = get(cellIdx);
		container->emplace(value);
	}

	void set(const mathfu::vec2i& cellIdx, T&& value)
	{
		set(cellIdx, std::move(value));
	}

	void remove(const mathfu::vec2i& cellIdx, entt::entity value)
	{
		auto* container = get(cellIdx);
		container->erase(value);
	}


	std::unordered_set<T>* get(const mathfu::vec2& worldPos) {
		return get(toCellIdx(worldPos));
	}

	bool has(const mathfu::vec2i& cellIdx)
	{
		return data[sizeX * cellIdx.y + cellIdx.x].size()  > 0;
	}


	const std::vector<std::unordered_set<T>>& getData() {
		return data;
	}


	short getSizeX() {
		return sizeX;
	}

	short getSizeY() {
		return sizeY;
	}

	short getCellSize() {
		return cellSize;
	}

private:
	short sizeX;
	short sizeY;
	short cellSize;
	std::vector<std::unordered_set<T>> data;
	mathfu::vec2 offset;
};

