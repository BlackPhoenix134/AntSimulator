#pragma once
#include "entt.hpp"
#include "mathfu/glsl_mappings.h"


template <typename T>
class Grid
{
	//starts top left
public:

	
	Grid(short sizeX, short sizeY, int cellSize) : Grid<T>(sizeX, sizeY, cellSize, mathfu::kZeros2f) {
	}

	
	Grid(short sizeX, short sizeY, int cellSize, mathfu::vec2 offset) : sizeX(sizeX), sizeY(sizeY),
		cellSize(cellSize), offset(offset) {
		data.resize(sizeX * sizeY);
	}

	
	~Grid() {

	}

	
	mathfu::vec2i toCellIdx(const mathfu::vec2& worldPos) const
	{
		return mathfu::vec2i(floor((worldPos.x + offset.x) / cellSize), floor((worldPos.y + offset.y) / cellSize));
	}

	
	mathfu::vec2 toWorldPos(const mathfu::vec2i& cellIdx) const
	{
		return mathfu::vec2(cellIdx.x * cellSize - offset.x, cellIdx.y * cellSize - offset.y);
	}

	
	T* get(const mathfu::vec2i& cellIdx) {
		return &data[sizeX * cellIdx.y + cellIdx.x];
	}

	void set(const mathfu::vec2i& cellIdx, const T& value)
	{
		data[sizeX * cellIdx.y + cellIdx.x] = value;
	}

	void set(const mathfu::vec2i& cellIdx, T&& value)
	{
		data[sizeX * cellIdx.y + cellIdx.x] = std::move(value);
	}

	void remove(const mathfu::vec2i& cellIdx)
	{
		data[sizeX * cellIdx.y + cellIdx.x] = nullptr;
	}


	T* get(const mathfu::vec2& worldPos) {
		return get(toCellIdx(worldPos));
	}

	bool has(const mathfu::vec2i& cellIdx)
	{
		return data[sizeX * cellIdx.y + cellIdx.x] != nullptr;
	}

	
	const std::vector<T>& getData() {
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
	std::vector<T> data;
	mathfu::vec2 offset;
};