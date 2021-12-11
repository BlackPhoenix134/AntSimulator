#pragma once
#include<raylib.h>

struct Point {
	int x;
	int y;

	bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}

	bool operator<(const Point& p)  const {
		return x < p.x || (x == p.x && y < p.y);
	}
};