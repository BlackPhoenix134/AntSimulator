#pragma once
#include "entt.hpp"
#include "SpatialHash.hpp"
#include "Grid.hpp"

namespace Systems {
    void loadTextures(entt::registry& registry);
    void render(entt::registry& registry);
    void renderAABB(entt::registry& registry);
    void renderSpatialHash(entt::registry& registry, SpatialHash& spatialHash);
    void renderVelocity(entt::registry& registry);
    void renderWorldGridEntries(Grid<std::unique_ptr<WorldGridEntry>>& grid);

    void applyVelocity(entt::registry& registry, float delta);


    void antBirth(entt::registry& registry);
    void antRandomMovement(entt::registry& registry);
    void antSensePheromones(entt::registry& registry, Grid<std::unique_ptr<WorldGridEntry>>& grid);
    void antLifetime(entt::registry& registry, float delta);
    void antDeath(entt::registry& registry);
    void antBringFoodHome(entt::registry& registry);


    void handleSpatialHashRegistration(entt::registry& registry, SpatialHash& grid);
    void antDropPheromones(entt::registry& registry, float delta, Grid<std::unique_ptr<WorldGridEntry>>& grid);
    void pheromoneLifetime(float delta, Grid<std::unique_ptr<WorldGridEntry>>& spatialHash);

}

