#pragma once
#include <raylib.h>
#include "Settings.hpp"
#include "mathfu/glsl_mappings.h"
#include "Settings.hpp"
namespace Comps {
	struct Ant {
		float lifetime = Settings::ANT_LIFE_TIME;
		float moveSpeed = Settings::ANT_MOVE_SPEED;
		float pheromoneDetectionDistance = Settings::ANT_PHEROMONE_DETECTION_DISTANCE;
	};

	struct Newborn {

	};

	struct Home {
		mathfu::vec2 position = mathfu::vec2(0, 0);
	};

	struct HasFood {
		
	};
}