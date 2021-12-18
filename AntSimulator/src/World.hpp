#pragma once
#include"entt.hpp"
#include "aspch.hpp"


class World {
private:

    Context context = Context();
    void updateRendering(Context& context);
    void updateDebugRendering(Context& context);
    void updatePhysics(Context& context);
    void updateAntLogic(Context& context);
    void updatePheromoneLogic(Context& context);
public:
    World();
    ~World();
    void update(float delta);
    void fixedUpdate(float delta);
    void updateUI(float delta);
};

