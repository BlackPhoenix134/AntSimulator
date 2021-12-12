#define RAYGUI_IMPLEMENTATION
#include "aspch.hpp"
#include "raylib.h"
#include "entt.hpp"
#include "World.hpp"
#include <memory>

constexpr auto SCREEN_WIDTH = 1920;
constexpr auto SCREEN_HEIGHT = 1080;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);
    int tick = 0;

    Vector2 camFollowPoint = { 0,0 };
    Camera2D camera = { 0 };
    camera.target = camFollowPoint;
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    entt::registry registry;

    std::unique_ptr<World> world(new World());

    for (auto i = 0; i < 100; ++i) {
        auto entity = Prefabs::createAnt(registry, { 0,0 });
    }


    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_W)) camFollowPoint.y -= 2;
        else if (IsKeyDown(KEY_S)) camFollowPoint.y += 2;
        if (IsKeyDown(KEY_A)) camFollowPoint.x -= 2;
        else if (IsKeyDown(KEY_D)) camFollowPoint.x += 2;
        camera.target = camFollowPoint;
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        if (camera.zoom > 20.0f) camera.zoom = 20.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;


        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        float delta = GetFrameTime();
        //ToDo: physics step frame skip
        world->update(registry, delta);
        world->fixedUpdate(registry, delta);
        tick++;
        DrawLine((int)camera.target.x, -SCREEN_HEIGHT * 10, (int)camera.target.x, SCREEN_HEIGHT * 10, GREEN);
        DrawLine(-SCREEN_WIDTH * 10, (int)camera.target.y, SCREEN_WIDTH * 10, (int)camera.target.y, GREEN);

        EndMode2D();

        world->updateUI(registry);

        DrawText("SCREEN AREA", 640, 10, 20, RED);

        DrawRectangle(0, 0, SCREEN_WIDTH, 5, RED);
        DrawRectangle(0, 5, 5, SCREEN_HEIGHT - 10, RED);
        DrawRectangle(SCREEN_WIDTH - 5, 5, 5, SCREEN_HEIGHT - 10, RED);
        DrawRectangle(0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5, RED);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

