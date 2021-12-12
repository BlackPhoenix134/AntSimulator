#include "Grid.hpp"
#include "mathfu/constants.h"
#include "aspch.hpp"

template <typename T>
Grid<T>::Grid(short sizeX, short sizeY, int cellSize): Grid<T>(sizeX, sizeY, cellSize, mathfu::kZeros2f) {
}

template <typename T>
Grid<T>::Grid(short sizeX, short sizeY, int cellSize, mathfu::vec2 offset) : sizeX(sizeX), sizeY(sizeY),
		cellSize(cellSize), offset(offset) {
	data.resize(sizeX * sizeY);
}

template <typename T>
Grid<T>::~Grid() {
	
}

template <typename T>
mathfu::vec2i Grid<T>::toCellIdx(const mathfu::vec2& worldPos) const 
{
	return mathfu::vec2i(floor((worldPos.x + offset.x) / cellSize), floor((worldPos.y + offset.y) / cellSize));
}

template <typename T>
mathfu::vec2 Grid<T>::toWorldPos(const mathfu::vec2i& cellIdx) const
{
	return mathfu::vec2(cellIdx.x * cellSize - offset.x, cellIdx.y * cellSize - offset.y);
}


template <typename T>
T* Grid<T>::get(const mathfu::vec2i& cellIdx) {
	return &data[sizeX * cellIdx.y + cellIdx.x];
}

template<typename T>
void Grid<T>::set(const mathfu::vec2i& cellIdx, T& value)
{
	data[sizeX * cellIdx.y + cellIdx.x] = value;
}

template<typename T>
void Grid<T>::set(const mathfu::vec2i& cellIdx, T&& value)
{
	data[sizeX * cellIdx.y + cellIdx.x] = std::move(value);
}

template <typename T>
T* Grid<T>::get(const mathfu::vec2& worldPos) {
	return get(toCellIdx(worldPos));
}

template<typename T>
bool Grid<T>::has(const mathfu::vec2i& cellPos)
{
	return true;
}

template <typename T>
const std::vector<T>& Grid<T>::getData() {
	return data;
}


template <typename T>
short Grid<T>::getSizeX() {
	return sizeX;
}

template <typename T>
short Grid<T>::getSizeY() {
	return sizeY;
}

template <typename T>
short Grid<T>::getCellSize() {
	return cellSize;
}

template class Grid<std::unique_ptr<WorldGridEntry>>;