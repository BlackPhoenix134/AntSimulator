#pragma once
#include"entt.hpp"
#include "aspch.hpp"


class World {
private:
    Context context = Context();
    void updateRendering(Context& context);
    void updatePhysics(Context& context);
    void updateAntLogic(Context& context);
    void updatePheromoneLogic(Context& context);
public:
    World(Camera2D* camera);
    ~World();
    void update(float delta);
    void fixedUpdate(float delta);
    void updateUI(float delta);
};

