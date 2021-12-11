#pragma once
#include"SpatialHash.hpp"
#include "entt.hpp"

SpatialHash::SpatialHash(int cellSize)
{
	this->cellSize = cellSize;
}


SpatialHash::~SpatialHash(void)
{
}

mathfu::vec2i SpatialHash::toCellIdx(const mathfu::vec2& position) //ToDo: weird stuff
{
	return mathfu::vec2i(floor(position.x / cellSize), floor(position.y / cellSize));
}

void SpatialHash::add(const mathfu::vec2i& point, entt::entity value)
{
	if (has(point))
	{
		data[point].insert(value);
	}
	else
	{
		std::unordered_set<entt::entity> container;
		data[point] = container;
		data[point].insert(value);
	}

}

void SpatialHash::add(const mathfu::vec2& position, const mathfu::vec2& size, entt::entity value)
{
	auto topLeft = toCellIdx(mathfu::vec2(position.x - size.x / 2, position.y - size.y / 2));
	auto botRight = toCellIdx(mathfu::vec2(position.x + size.x / 2, position.y + size.y / 2));

	for (int i = topLeft.x; i <= botRight.x; i++) {
		for (int j = topLeft.y; j <= botRight.y; j++) {
			add(mathfu::vec2i(i, j), value);
		}
	}
}

void SpatialHash::remove(const mathfu::vec2& position, const mathfu::vec2& size, entt::entity value)
{
	auto topLeft = toCellIdx(mathfu::vec2(position.x - size.x / 2, position.y - size.y / 2));
	auto botRight = toCellIdx(mathfu::vec2(position.x + size.x / 2, position.y + size.y / 2));

	for (int i = topLeft.x; i <= botRight.x; i++) {
		for (int j = topLeft.y; j <= botRight.y; j++) {
			remove(mathfu::vec2i(i, j), value);
		}
	}
}


void SpatialHash::remove(const mathfu::vec2i& point, entt::entity value)
{
	if (has(point))
	{
		auto& container = data[point];
		bool before = container.find(value) != container.end();
		container.erase(value);
		if (container.size() == 0) {
			auto beforeContainer = has(point);
			auto sizeBefore = data.size();
			data.erase(point);
			printf("found before %d found after %d size %d size after %d\n", beforeContainer, has(point), sizeBefore, data.size());
		}
	}
}

const std::unordered_set<entt::entity>& SpatialHash::get(const mathfu::vec2i& point) {
	return data.at(point);
}

bool SpatialHash::has(const mathfu::vec2i& point) {
	return data.find(point) != data.end();
}

bool SpatialHash::has(const mathfu::vec2& position) {
	return has(toCellIdx(position));
}

int SpatialHash::getCellSize() {
	return cellSize;
}

const std::unordered_map<mathfu::vec2i, std::unordered_set<entt::entity>, Hasher>& SpatialHash::getData() {
	return data;
}