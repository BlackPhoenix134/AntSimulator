#pragma once
#include"entt.hpp"
#include "aspch.hpp"

constexpr short spatialHashCellSize = 100;
constexpr short gridSize = 500;
constexpr short gridCellSize(25);


class World {
private:

    SpatialHash spatialHash = SpatialHash(spatialHashCellSize);
    Grid<std::unique_ptr<WorldGridEntry>> grid =
        Grid<std::unique_ptr<WorldGridEntry>>(gridSize, gridSize, gridCellSize, mathfu::vec2(gridSize / 2 * gridCellSize));
    void updateRendering(entt::registry& registry, float delta);
    void updateDebugRendering(entt::registry& registry, float delta);
    void updatePhysics(entt::registry& registry, float delta);
    void updateAntLogic(entt::registry& registry, float delta);
    void updatePheromoneLogic(entt::registry& registry, float delta);
public:
    World();
    ~World();
    void update(entt::registry& registry, float delta);
    void fixedUpdate(entt::registry& registry, float delta);
    void updateUI(entt::registry& registry);
};

