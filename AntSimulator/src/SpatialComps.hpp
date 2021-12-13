#pragma once
#include <raylib.h>
#include <mathfu/glsl_mappings.h>
#include <mathfu/constants.h>
#include "VectorUtils.hpp"

namespace Comps {
	struct Trans {
		mathfu::vec2 position = mathfu::vec2(0, 0);
		mathfu::vec2 scale = mathfu::vec2(1, 1);

		float rotation = 0;

		mathfu::vec2 getForward() const {
			return vectorFromRotation(rotation);
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