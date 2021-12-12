#pragma once
#include "entt.hpp"
#include <raylib.h>
#include "mathfu/glsl_mappings.h"
#include "AntBrainComps.hpp"

namespace Prefabs {
	entt::entity createAnt(entt::registry& registry, mathfu::vec2 position);
	entt::entity createFood(entt::registry& registry, mathfu::vec2 position);
}