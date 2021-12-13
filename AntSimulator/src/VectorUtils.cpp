#include "VectorUtils.hpp"
#include <raylib.h>

mathfu::vec2 vectorFromRotation(float degrees) {
	float radians = degrees * (PI / 180);
	float cosValue = cos(radians);
	float sinValue = sin(radians);
	return mathfu::vec2(cosValue, sinValue);
}