#include"Systems.hpp"
#include"SpatialComps.hpp"
#include"RenderComps.hpp"
#include"DebugComps.hpp"
#include"raylib.h"
#include"entt.hpp"
#include"AntBrainComps.hpp"
#include"AssetManager.hpp"
#include"GeneralComps.hpp"
#include"Prefabs.hpp"
#include "random.hpp"
#include "Settings.hpp"

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

    void antSensePheromones(entt::registry& registry)
    {
        //ToDo: check in vicinity 
        //auto view = registry.view<const Comps::Trans, const Comps::Ant>(entt::exclude<Comps::HasFood>);
        //get pheromones, steer towards other ants, or follow food
        //ToDo: rotate forward
    }

    void antFollowTrail(entt::registry& registry)
    {

    }

    void antDropPheromones(entt::registry& registry, float delta)
    {
        auto view = registry.view<Comps::Ant, const Comps::Trans, const Comps::Alive>();
        view.each([&registry, &delta](const entt::entity entity, Comps::Ant& ant, const Comps::Trans& trans) {
            ant.nextMarkerCooldown -= delta;
            if (ant.nextMarkerCooldown <= 0) {
                ant.nextMarkerCooldown = Settings::ANT_NEXT_MARKER_COOLDOWN;

                Comps::PheromoneType type = Comps::PheromoneType::AntPrecense;
                if (registry.any_of<Comps::HasFood>(entity))
                    type = Comps::PheromoneType::ToFood;
                Prefabs::createPheromone(registry, trans.position, type);
            }
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
            registry.emplace<Comps::SpatiallyHashed>(entity);
            registry.remove<Comps::StaticSpatialRegister>(entity);
            });
    }

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

    void pheromoneLifetime(entt::registry& registry, float delta)
    {
    /*    auto view = registry.view<Comps::Pheromone, const Comps::Trans, const Comps::SpriteRender>();
        view.each([&registry, &delta, &spatialHash](entt::entity entity, Comps::Pheromone& phero,
                const Comps::Trans& trans, const Comps::SpriteRender& spriteRender) {
            phero.lifeTime -= delta;
            if (phero.lifeTime <= 0) {
                spatialHash.remove(trans.position, mathfu::vec2(spriteRender.width(), spriteRender.height()), entity);
                registry.destroy(entity);
            }
            });*/
    }
}