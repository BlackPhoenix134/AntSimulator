#include "VectorUtils.hpp"
#include <raylib.h>

mathfu::vec2 vectorFromRotation(float degrees) {
	float radians = degrees * (PI / 180);
	float cosValue = cos(radians);
	float sinValue = sin(radians);
	return mathfu::vec2(cosValue, sinValue);
}

bool intersects(mathfu::rectf a, mathfu::rectf b)
{
	return (abs((a.pos.x + a.size.x / 2) - (b.pos.x + b.size.x / 2)) * 2 < (a.size.x + b.size.x)) &&
		(abs((a.pos.y + a.size.y / 2) - (b.pos.y + b.size.y / 2)) * 2 < (a.size.y + b.size.y));
}

bool intersects(mathfu::rectf a, mathfu::vec2 b)
{
	return (b.x > a.pos.x && b.x < (a.pos.x + a.size.x) &&
		b.y > a.pos.y && b.y < a.pos.y + a.size.y);
}
