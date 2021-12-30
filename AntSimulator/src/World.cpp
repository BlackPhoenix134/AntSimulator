#include "World.hpp"
#include "Systems.hpp"


World::World(Camera2D* camera)
{
    context.camera2D = camera;

    for (auto i = 0; i < 100; ++i) {
        auto entity = Prefabs::createAnt(context.registry, { 0,0 });
    }

    auto& walls = context.worldWalls;
    for (int x = 0; x < walls.getSizeX(); x++) {
        context.worldWalls.set(mathfu::vec2i(x, 0), 1);
        context.worldWalls.set(mathfu::vec2i(x, walls.getSizeY() - 1), 1);
    }

    for (int y = 0; y < walls.getSizeY(); y++) {
        context.worldWalls.set(mathfu::vec2i(0, y), 1);
        context.worldWalls.set(mathfu::vec2i(walls.getSizeX() - 1, y), 1);
    }
}

World::~World()
{
}

void World::update(float delta) {
    context.deltaTime = delta;
    Systems::applyVelocity(context);

    updateRendering(context);
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
    auto cam = *context.camera2D;
    auto topLeft = GetScreenToWorld2D({ 0,0 }, cam);
    auto botRight = GetScreenToWorld2D({ (float)GetScreenWidth(),(float)GetScreenHeight() }, cam);

    mathfu::rectf viewport = mathfu::rectf(topLeft.x, topLeft.y, botRight.x - topLeft.x, botRight.y - topLeft.y);
    Systems::renderWorldGridCells(context, viewport);
    Systems::render(context, viewport);
    Systems::renderWorldWalls(context, viewport);

    Systems::renderSpatialHash(context, viewport);
    Systems::renderVelocity(context, viewport);
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
