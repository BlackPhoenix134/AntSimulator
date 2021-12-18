#pragma once
#include "mathfu/glsl_mappings.h"

mathfu::vec2 vectorFromRotation(float degrees);
bool intersects(mathfu::rectf a, mathfu::rectf b); 
bool intersects(mathfu::rectf a, mathfu::vec2 b);
