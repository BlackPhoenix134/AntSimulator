#pragma once
#include "entt.hpp"
#include "SpatialHash.hpp"
#include "Grid.hpp"
#include "Context.hpp"
#include "mathfu/rect.h"

namespace Systems {
    void loadTextures(Context& context);

    void render(Context& context, mathfu::rectf& viewport);
    void renderSpatialHash(Context& context, mathfu::rectf& viewport);
    void renderVelocity(Context& context, mathfu::rectf& viewport);
    void renderWorldGridEntries(Context& context, mathfu::rectf& viewport);
    void renderWorldWalls(Context& context, mathfu::rectf& viewport);

    void applyVelocity(Context& context);


    void antBirth(Context& context);
    void antRandomMovement(Context& context);
    void antSensePheromones(Context& context);
    void antLifetime(Context& context);
    void antDeath(Context& context);
    void antBringFoodHome(Context& context);


    void handleSpatialHashRegistration(Context& context);
    void antDropPheromones(Context& context);
    void pheromoneLifetime(Context& context);
}

