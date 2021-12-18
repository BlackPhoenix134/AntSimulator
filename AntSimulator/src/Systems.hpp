#pragma once
#include "entt.hpp"
#include "SpatialHash.hpp"
#include "Grid.hpp"
#include "Context.hpp"

namespace Systems {
    void loadTextures(Context& context);
    void render(Context& context);
    void renderAABB(Context& context);
    void renderSpatialHash(Context& context);
    void renderVelocity(Context& context);
    void renderWorldGridEntries(Context& context);
    void renderWorldWalls(Context& context);

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

