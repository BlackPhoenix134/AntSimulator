#pragma once
#include<raylib.h>
#include <mathfu/glsl_mappings.h>
#include <mathfu/constants.h>

namespace Comps {
	struct Trans {
		mathfu::vec2 position = mathfu::vec2(0, 0);
		mathfu::vec2 scale = mathfu::vec2(1, 1);

		float rotation = 0;

		mathfu::vec2 getForward() const {
			float radians = rotation * (PI / 180);
			float cosValue = cos(radians);
			float sinValue = sin(radians);
			return mathfu::vec2(cosValue, sinValue);
		}
	};

	struct Velocity {
		mathfu::vec2 value = mathfu::vec2(0, 0);
	};

	struct StaticSpatialRegister {

	};

	struct SpatialHashEntry {

	};

	struct GridEntryRegister {
	};

	struct GridEntry {
		mathfu::vec2i cellIdx;
	};
}