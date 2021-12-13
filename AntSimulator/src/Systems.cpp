#include "aspch.hpp"
#include "Systems.hpp"
#include "raylib.h"
#include "random.hpp"
#include "entt.hpp"

namespace Systems {
    void loadTextures(entt::registry& registry) {
        auto view = registry.view<const Comps::TextureStr, Comps::SpriteRender>();
        view.each([&registry](const entt::entity entity, const Comps::TextureStr& textureStr, Comps::SpriteRender& spriteRender) {
            spriteRender.texture = Assets::get(textureStr.name.c_str());
            registry.remove<Comps::TextureStr>(entity);
            });
    }

    void render(entt::registry& registry) {
        auto view = registry.view<const Comps::Trans, Comps::SpriteRender>();
        view.each([](const Comps::Trans& trans, Comps::SpriteRender& spriteRender) {
            float width = spriteRender.width();
            float height = spriteRender.height();
            Rectangle destination = { trans.position.x, trans.position.y , width, height };
            DrawTexturePro(spriteRender.texture, spriteRender.sourceRect, destination, {width/2, height/2}, trans.rotation, spriteRender.tint);
            DrawRectangleLines(trans.position.x - width / 2, trans.position.y - height / 2, width, height, RED);
            });
    }


    void renderWorldGridEntries(Grid<std::unique_ptr<WorldGridEntry>>& grid) {
        for (int x = 0; x < grid.getSizeX(); x++) {
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
        }
    }

    void renderAABB(entt::registry& registry) {
        auto view = registry.view<const Comps::Trans, Comps::SpriteRender, const Comps::ShowAABB>();
        view.each([](const Comps::Trans& trans, Comps::SpriteRender& spriteRender) {
            float width = spriteRender.width();
            float height = spriteRender.height();
            DrawRectangleLines(trans.position.x - width / 2, trans.position.y - height / 2, width, height, RED);
            });
    }

    void applyVelocity(entt::registry& registry, float delta) {
        auto view = registry.view<Comps::Trans, const Comps::Velocity>();
        view.each([&delta](Comps::Trans& trans, const Comps::Velocity& velocity) {
            trans.position.x += velocity.value.x * delta;
            trans.position.y += velocity.value.y * delta;
            });
    }

    
    void antBirth(entt::registry& registry)
    {
        auto view = registry.view<Comps::Trans, const Comps::Ant, const Comps::Newborn>();
        view.each([&registry](const entt::entity entity, Comps::Trans& trans, const Comps::Ant) {
            trans.rotation = randomFloat(0.f, 360.f);
            registry.remove<Comps::Newborn>(entity);
            });
    }

    void antRandomMovement(entt::registry& registry)
    {
        auto view = registry.view<const Comps::Trans, Comps::Velocity, const Comps::Ant>();
        view.each([&registry](const entt::entity entity, const Comps::Trans& trans, Comps::Velocity& vel, const Comps::Ant ant) {
            mathfu::vec2 direction = trans.getForward();
            vel.value.x = direction.x * ant.moveSpeed;
            vel.value.y = direction.y * ant.moveSpeed;
            });
    }

    void antSensePheromones(entt::registry& registry, Grid<std::unique_ptr<WorldGridEntry>>& grid)
    {
        auto view = registry.view<const Comps::Trans, Comps::Velocity, const Comps::Ant>();
        view.each([&registry, &grid](const entt::entity entity, const Comps::Trans& trans, Comps::Velocity& vel, const Comps::Ant ant) {
            mathfu::vec2 up = vectorFromRotation(trans.rotation);
            mathfu::vec2 upLeft = vectorFromRotation(trans.rotation - 45);
            mathfu::vec2 upRight = vectorFromRotation(trans.rotation + 45);
            float size = grid.getCellSize();
            mathfu::vec2i upCell = grid.toCellIdx(trans.position + up * size);
            mathfu::vec2i upLeftCell = grid.toCellIdx(trans.position + upLeft * size);
            mathfu::vec2i upRightCell = grid.toCellIdx(trans.position + upRight * size);


            });
    }


    void antDropPheromones(entt::registry& registry, float delta, Grid<std::unique_ptr<WorldGridEntry>>& grid)
    {
        auto view = registry.view<Comps::Ant, const Comps::Trans, const Comps::Alive>();
        view.each([&registry, &grid, &delta](const entt::entity entity, Comps::Ant& ant, const Comps::Trans& trans) {
            auto& cellIdx = grid.toCellIdx(trans.position);
            
            PheromoneType type = PheromoneType::AntPrecense;
            if (registry.any_of<Comps::HasFood>(entity))
                type = PheromoneType::ToFood;
            grid.set(grid.toCellIdx(trans.position - trans.getForward() * 10.f), std::unique_ptr<Pheromone>(new Pheromone(type)));
        });
    }

    void antLifetime(entt::registry& registry, float delta)
    {
        auto view = registry.view<Comps::Ant, const Comps::Alive>();
        view.each([&registry, &delta](const entt::entity entity, Comps::Ant& ant) {
            ant.lifetime -= delta;
            if (ant.lifetime <= 0) {
                registry.emplace<Comps::Dead>(entity);
                registry.remove<Comps::Alive>(entity);
            }
        });
    }

    void antDeath(entt::registry& registry)
    {
        auto view = registry.view<Comps::Ant, const Comps::Trans, const Comps::Dead>();
        view.each([&registry](const entt::entity entity, Comps::Ant& ant, const Comps::Trans& trans) {
            Prefabs::createFood(registry, trans.position);
            registry.destroy(entity);
        });
    }

    void antBringFoodHome(entt::registry& registry)
    {
    }

    void handleSpatialHashRegistration(entt::registry& registry, SpatialHash& spatialHash)
    {
        auto view = registry.view<const Comps::Trans, Comps::SpriteRender, const Comps::StaticSpatialRegister>();
        view.each([&registry, &spatialHash](const entt::entity entity, const Comps::Trans& trans, Comps::SpriteRender& spriteRender) {
            float width = spriteRender.width();
            float height = spriteRender.height();
            spatialHash.add(trans.position, { width, height }, entity);
            registry.emplace<Comps::SpatialHashEntry>(entity);
            registry.remove<Comps::StaticSpatialRegister>(entity);
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


    void renderSpatialHash(entt::registry& registry, SpatialHash& spatialHash)
    {
        float cellSize = spatialHash.getCellSize();
        for (const auto& kv : spatialHash.getData()) {
            const auto& point = kv.first;
            DrawRectangleLines(point.x * cellSize, point.y * cellSize, cellSize, cellSize, BLUE);
        }
    }

    void renderVelocity(entt::registry& registry)
    {
        auto view = registry.view<const Comps::Trans, const Comps::Velocity>();
        view.each([&registry](const Comps::Trans& trans, const Comps::Velocity& vel) {
            DrawLine(trans.position.x, trans.position.y, trans.position.x + vel.value.x, trans.position.y + vel.value.y, RED);
            });
    }

    

    void pheromoneLifetime(float delta, Grid<std::unique_ptr<WorldGridEntry>>& grid) {
        for (int x = 0; x < grid.getSizeX(); x++) {
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
        }
    }
}