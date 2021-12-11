#pragma once
#include <raylib.h>
#include "Settings.hpp"
#include "mathfu/glsl_mappings.h"
#include "Settings.hpp"
namespace Comps {
	enum class PheromoneType :uint8_t {
		AntPrecense, ToFood
	};

	struct Ant {
		float lifetime = Settings::ANT_LIFE_TIME;
		float moveSpeed = Settings::ANT_MOVE_SPEED;
		float pheromoneDetectionDistance = Settings::ANT_PHEROMONE_DETECTION_DISTANCE;
		float nextMarkerCooldown = Settings::ANT_NEXT_MARKER_COOLDOWN;
	};

	struct Newborn {

	};

	struct Home {
		mathfu::vec2 position = mathfu::vec2(0, 0);
	};

	struct HasFood {
		
	};

	
	struct Pheromone {
		 PheromoneType type = PheromoneType::AntPrecense;
		 float lifeTime = Settings::PHEROMONE_LIFETIME;
	};

}