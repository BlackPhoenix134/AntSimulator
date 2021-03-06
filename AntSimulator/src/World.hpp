#pragma once
#include"entt.hpp"
#include "aspch.hpp"

constexpr int spatialHashCellSize = 100;
constexpr int gridSize = 500;
constexpr int gridCellSize = 20;

class World {
private:

    SpatialHash spatialHash = SpatialHash(spatialHashCellSize);
    Grid<Pheromone> grid = Grid<Pheromone>(gridSize, gridSize, gridCellSize, mathfu::vec2(gridSize / 2 * gridCellSize));
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

