#pragma once
#include <iostream>
#include <map>
#include <raylib.h>
#include "entt.hpp"
#include "mathfu/glsl_mappings.h"


class Hasher
{
public:
	int operator()(const mathfu::vec2i& vec) const {
		int ret = 0;
		ret ^= std::hash<int>()(vec.x);
		ret ^= std::hash<int>()(vec.y);
		return ret;
	}
};

class EqualFn
{
public:
	bool operator() (const mathfu::vec2i& t1, mathfu::vec2i& t2) const {
		return t1.x == t2.x && t1.y == t2.y;
	}
};


class SpatialHash
{
	private:
		int cellSize;
		std::unordered_map<mathfu::vec2i, std::unordered_set<entt::entity>, Hasher> data;
	public:
		SpatialHash(int cellSize);
		~SpatialHash(void);
		mathfu::vec2i toCellIdx(const mathfu::vec2& position);
		void add(const mathfu::vec2& position, entt::entity value);
		void add(const mathfu::vec2i& point, entt::entity value);
		void add(const mathfu::vec2& position, const mathfu::vec2& size, entt::entity value);
		void remove(const mathfu::vec2& position, entt::entity value);
		void remove(const mathfu::vec2& position, const mathfu::vec2& size, entt::entity value);
		void remove(const mathfu::vec2i& point, entt::entity value);
		const std::unordered_set<entt::entity>& get(const mathfu::vec2i& point);
		bool has(const mathfu::vec2i& point);
		bool has(const mathfu::vec2& position);
		int getCellSize();
		const std::unordered_map<mathfu::vec2i, std::unordered_set<entt::entity>, Hasher>& getData();
};
