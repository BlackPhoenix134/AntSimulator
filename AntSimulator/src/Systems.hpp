#pragma once
#include"entt.hpp"
#include"SpatialHash.hpp"

namespace Systems {
    void loadTextures(entt::registry& registry);
    void render(entt::registry& registry);
    void renderAABB(entt::registry& registry);
    void renderSpatialHash(entt::registry& registry, SpatialHash& spatialHash);
    void renderVelocity(entt::registry& registry);

    void applyVelocity(entt::registry& registry, float delta);


    void antBirth(entt::registry& registry);
    void antRandomMovement(entt::registry& registry);
    void antSensePheromones(entt::registry& registry);
    void antFollowTrail(entt::registry& registry);
    void antDropPheromones(entt::registry& registry, float delta);
    void antLifetime(entt::registry& registry, float delta);
    void antDeath(entt::registry& registry);
    void antBringFoodHome(entt::registry& registry);

    void pheromoneLifetime(entt::registry& registry, float delta);


    void handleSpatialHashRegistration(entt::registry& registry, SpatialHash& spatialHash);

}

