#pragma once
#include "entt.hpp"
#include "mathfu/glsl_mappings.h"
template <typename T>
class Grid
{
	//starts top left
public:
	Grid(short sizeX, short sizeY, int cellSize);
	Grid(short sizeX, short sizeY, int cellSize, mathfu::vec2 offset);
	~Grid();
	mathfu::vec2i toCellIdx(const mathfu::vec2& worldPos) const;
	mathfu::vec2 toWorldPos(const mathfu::vec2i& cellIdx) const;
	T* get(const mathfu::vec2& worldPos);
	T* get(const mathfu::vec2i& cellIdx);
	void set(const mathfu::vec2i& cellIdx, const T& value);
	void set(const mathfu::vec2i& cellIdx, T&& value);
	bool has(const mathfu::vec2i& cellPos);
	const std::vector<T>& getData();
	short getSizeX();
	short getSizeY();
	short getCellSize();
private:
	short sizeX;
	short sizeY;
	short cellSize;
	std::vector<T> data;
	mathfu::vec2 offset;
};

