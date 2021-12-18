#include "World.hpp"
#include "Systems.hpp"


World::World()
{
    for (auto i = 0; i < 100; ++i) {
        auto entity = Prefabs::createAnt(context.registry, { 0,0 });
    }
}

World::~World()
{
}

void World::update(float delta) {
    context.deltaTime = delta;
    Systems::applyVelocity(context);

    updateRendering(context);
    updateDebugRendering(context);
}

void World::fixedUpdate(float delta) {
    context.deltaTime = delta;
    updatePhysics(context);
    updateAntLogic(context);
    updatePheromoneLogic(context);
}

void World::updateUI(float delta)
{
    context.deltaTime = delta;
}


void World::updateRendering(Context& context)
{
    Systems::loadTextures(context);
    Systems::renderWorldGridEntries(context);
    Systems::render(context);
}

void World::updateDebugRendering(Context& context)
{
    Systems::renderAABB(context);
    Systems::renderSpatialHash(context);
    Systems::renderVelocity(context);
}

void World::updatePhysics(Context& context)
{
    Systems::handleSpatialHashRegistration(context);
}

void World::updateAntLogic(Context& context)
{
    Systems::antBirth(context);
    Systems::antLifetime(context);
    Systems::antDeath(context);

    Systems::antRandomMovement(context);
    Systems::antSensePheromones(context);
    Systems::antDropPheromones(context);
    Systems::antBringFoodHome(context);
}

void World::updatePheromoneLogic(Context& context)
{
    Systems::pheromoneLifetime(context);
}
