#include "World.hpp"
#include "Systems.hpp"


World::World()
{

}

World::~World()
{
}

void World::update(entt::registry& registry, float delta) {
    Systems::applyVelocity(registry, delta);

    updateRendering(registry, delta);
    updateDebugRendering(registry, delta);
}

void World::fixedUpdate(entt::registry& registry, float delta) {
    updatePhysics(registry, delta);
    updateAntLogic(registry, delta);
    updatePheromoneLogic(registry, delta);
}

void World::updateUI(entt::registry& registry)
{
    
}


void World::updateRendering(entt::registry& registry, float delta)
{
    Systems::loadTextures(registry);
    Systems::renderPheromones(grid);
    Systems::render(registry);
}

void World::updateDebugRendering(entt::registry& registry, float delta)
{
    Systems::renderAABB(registry);
    Systems::renderSpatialHash(registry, spatialHash);
    Systems::renderVelocity(registry);
}

void World::updatePhysics(entt::registry& registry, float delta)
{
    Systems::handleSpatialHashRegistration(registry, spatialHash);
}

void World::updateAntLogic(entt::registry& registry, float delta) 
{
    Systems::antBirth(registry);

    Systems::antLifetime(registry, delta);
    Systems::antDeath(registry);
    

    Systems::antRandomMovement(registry);
    Systems::antDropPheromones(registry, delta, grid);
    Systems::antSensePheromones(registry);
    Systems::antFollowTrail(registry);
    Systems::antBringFoodHome(registry);
}

void World::updatePheromoneLogic(entt::registry& registry, float delta)
{
    Systems::pheromoneLifetime(delta, grid);
}
