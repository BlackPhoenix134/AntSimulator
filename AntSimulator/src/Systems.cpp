#include "aspch.hpp"
#include "Systems.hpp"
#include "raylib.h"
#include "random.hpp"
#include "entt.hpp"

namespace Systems {
    void loadTextures(Context& context) {
        auto view = context.registry.view<const Comps::TextureStr, Comps::SpriteRender>();
        view.each([&context](const entt::entity entity, const Comps::TextureStr& textureStr, Comps::SpriteRender& spriteRender) {
            spriteRender.texture = Assets::get(textureStr.name.c_str());
            context.registry.remove<Comps::TextureStr>(entity);
            });
    }

    void render(Context& context, mathfu::rectf& viewport) {
        auto view = context.registry.view<const Comps::Trans, Comps::SpriteRender>();
        view.each([&](entt::entity entity, const Comps::Trans& trans, Comps::SpriteRender& spriteRender) {
            float width = spriteRender.width();
            float height = spriteRender.height();
            if (intersects(viewport, { trans.position.x, trans.position.y , width, height })) {
                Rectangle destination = { trans.position.x, trans.position.y , width, height };
                DrawTexturePro(spriteRender.texture, spriteRender.sourceRect, destination, { width / 2, height / 2 }, trans.rotation, spriteRender.tint);
               
                if (context.registry.all_of<Comps::ShowAABB>(entity)) {
                    DrawRectangleLines(trans.position.x - width / 2, trans.position.y - height / 2, width, height, RED);
                }
            
            }
        });
    }


    void renderWorldGridEntries(Context& context, mathfu::rectf& viewport) {
       /* for (int x = 0; x < grid.getSizeX(); x++) {
            for (int y = 0; y < grid.getSizeY(); y++) {
                auto cellPos = mathfu::vec2i(x, y);
                auto* entry = grid.get(cellPos)->get();
                if (entry != nullptr) {
                    auto texture = entry->getTexture();
                    auto worldPos = grid.toWorldPos(cellPos);

                    float destWidth = texture.width * grid.getCellSize() / texture.width;
                    float destHeight = texture.height * grid.getCellSize() / texture.height;

                    DrawTexturePro(texture, { 0, 0, (float)texture.width, (float)texture.height },
                        { worldPos.x, worldPos.y, destWidth, destHeight },
                        { destWidth / 2, destHeight / 2 }, 0, entry->getColor());
                }
            }
        }*/
    }

    void renderWorldWalls(Context& context, mathfu::rectf& viewport)
    {
         auto& worldWalls = context.worldWalls;
         auto texture = Assets::get("assets/marker.png");
         float width = texture.width * worldWalls.getCellSize() / texture.width;
         float height = texture.height * worldWalls.getCellSize() / texture.height;

         for (int x = 0; x < worldWalls.getSizeX(); x++) {
             for (int y = 0; y < worldWalls.getSizeY(); y++) {
                 if (*worldWalls.get(mathfu::vec2i(x, y)) == 1) {
                     auto pos = worldWalls.toWorldPos(mathfu::vec2i(x, y));

                     if (intersects(viewport, { pos.x, pos.y , width, height })) {
                         Rectangle destination = { pos.x, pos.y , width, height };
                         DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height }, destination, { width / 2, height / 2 }, 0, RED);
                     }
                 }
             }
         }
    }

    void applyVelocity(Context& context) {
        auto view = context.registry.view<Comps::Trans, const Comps::Velocity>();
        view.each([&context](Comps::Trans& trans, const Comps::Velocity& velocity) {
            trans.position.x += velocity.value.x * context.deltaTime;
            trans.position.y += velocity.value.y * context.deltaTime;
            });
    }

    
    void antBirth(Context& context)
    {
        auto view = context.registry.view<Comps::Trans, const Comps::Ant, const Comps::Newborn>();
        view.each([&context](const entt::entity entity, Comps::Trans& trans, const Comps::Ant) {
            trans.rotation = randomFloat(0.f, 360.f);
            context.registry.remove<Comps::Newborn>(entity);
            });
    }

    void antRandomMovement(Context& context)
    {
        auto view = context.registry.view<const Comps::Trans, Comps::Velocity, const Comps::Ant>();
        view.each([&context](const entt::entity entity, const Comps::Trans& trans, Comps::Velocity& vel, const Comps::Ant ant) {
            mathfu::vec2 direction = trans.getForward();
            vel.value.x = direction.x * ant.moveSpeed;
            vel.value.y = direction.y * ant.moveSpeed;
            });
    }

    void antSensePheromones(Context& context)
    {
        auto view = context.registry.view<const Comps::Trans, Comps::Velocity, const Comps::Ant>();
        view.each([&context](const entt::entity entity, const Comps::Trans& trans, Comps::Velocity& vel, const Comps::Ant ant) {
          /*  mathfu::vec2 up = vectorFromRotation(trans.rotation);
            mathfu::vec2 upLeft = vectorFromRotation(trans.rotation - 45);
            mathfu::vec2 upRight = vectorFromRotation(trans.rotation + 45);
            float size = grid.getCellSize();
            mathfu::vec2i upCell = grid.toCellIdx(trans.position + up * size);
            mathfu::vec2i upLeftCell = grid.toCellIdx(trans.position + upLeft * size);
            mathfu::vec2i upRightCell = grid.toCellIdx(trans.position + upRight * size);*/


            });
    }


    void antDropPheromones(Context& context)
    {
        auto view = context.registry.view<Comps::Ant, const Comps::Trans, const Comps::Alive>();
        view.each([&context](const entt::entity entity, Comps::Ant& ant, const Comps::Trans& trans) {
          /*  auto& cellIdx = grid.toCellIdx(trans.position);
            
            PheromoneType type = PheromoneType::AntPrecense;
            if (registry.any_of<Comps::HasFood>(entity))
                type = PheromoneType::ToFood;
            grid.set(grid.toCellIdx(trans.position - trans.getForward() * 10.f), std::unique_ptr<Pheromone>(new Pheromone(type)));*/
        });
    }

    void antLifetime(Context& context)
    {
        auto view = context.registry.view<Comps::Ant, const Comps::Alive>();
        view.each([&context](const entt::entity entity, Comps::Ant& ant) {
            ant.lifetime -= context.deltaTime;
            if (ant.lifetime <= 0) {
                context.registry.emplace<Comps::Dead>(entity);
                context.registry.remove<Comps::Alive>(entity);
            }
        });
    }

    void antDeath(Context& context)
    {
        auto view = context.registry.view<Comps::Ant, const Comps::Trans, const Comps::Dead>();
        view.each([&context](const entt::entity entity, Comps::Ant& ant, const Comps::Trans& trans) {
            Prefabs::createFood(context.registry, trans.position);
            context.registry.destroy(entity);
        });
    }

    void antBringFoodHome(Context& context)
    {
    }

    void handleSpatialHashRegistration(Context& context)
    {
        auto view = context.registry.view<const Comps::Trans, Comps::SpriteRender, const Comps::StaticSpatialRegister>();
        view.each([&context](const entt::entity entity, const Comps::Trans& trans, Comps::SpriteRender& spriteRender) {
            float width = spriteRender.width();
            float height = spriteRender.height();
            context.spatialHash.add(trans.position, { width, height }, entity);
            context.registry.emplace<Comps::SpatialHashEntry>(entity);
            context.registry.remove<Comps::StaticSpatialRegister>(entity);
            });
    }

  /*  void handleGridRegistrationPheromones(entt::registry& registry, Grid<entt::entity>& grid)
    {
        auto view = registry.view<Comps::Trans, const Comps::Pheromone, const Comps::GridEntryRegister>();
        view.each([&registry, &grid](const entt::entity entity, Comps::Trans& trans, const Comps::Pheromone& pheromone) {
            auto& entry = registry.emplace<Comps::GridEntry>(entity);
            entry.cellIdx = grid.toCellIdx(trans.position);
           
            auto before = trans.position;
            trans.position = grid.toWorldPos(entry.cellIdx);
            registry.remove<Comps::GridEntryRegister>(entity);
            });
    }*/


    void renderSpatialHash(Context& context, mathfu::rectf& viewport)
    {
        float cellSize = context.spatialHash.getCellSize();
        for (const auto& kv : context.spatialHash.getData()) {
            const auto& point = kv.first;
            DrawRectangleLines(point.x * cellSize, point.y * cellSize, cellSize, cellSize, BLUE);
        }
    }

    void renderVelocity(Context& context, mathfu::rectf& viewport)
    {
        auto view = context.registry.view<const Comps::Trans, const Comps::Velocity>();
        view.each([&context](const Comps::Trans& trans, const Comps::Velocity& vel) {
            });
    }


    void pheromoneLifetime(Context& context) {
       /* for (int x = 0; x < grid.getSizeX(); x++) {
            for (int y = 0; y < grid.getSizeY(); y++) {
                auto cellPos = mathfu::vec2i(x, y);
                WorldGridEntry* entry = grid.get(cellPos)->get();
                Pheromone* pheromone = dynamic_cast<Pheromone*>(grid.get(cellPos)->get());
                if (pheromone != nullptr) {
                    pheromone->lifeTime -= delta;
                    if (pheromone->lifeTime <= 0)
                        grid.remove(cellPos);
                }
            }
        }*/
    }
}