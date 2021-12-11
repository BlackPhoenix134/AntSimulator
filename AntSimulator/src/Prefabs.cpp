#include "Prefabs.hpp"
#include "SpatialComps.hpp"
#include "RenderComps.hpp"
#include "AntBrainComps.hpp"
#include "GeneralComps.hpp"
#include "AssetManager.hpp"
#include "AntBrainComps.hpp"

namespace Prefabs {
	entt::entity Prefabs::createAnt(entt::registry& registry, mathfu::vec2 position)
	{
        const auto entity = registry.create();
        Comps::Trans& trans = registry.emplace<Comps::Trans>(entity);
        trans.position = position;
        registry.emplace<Comps::Velocity>(entity);
        auto& spriteRender = registry.emplace<Comps::SpriteRender>(entity);
        spriteRender.setTexture(Assets::get("assets/ant.png"));
        spriteRender.desiredDimensions = { 25 , 25 };

        Comps::Home& home = registry.emplace<Comps::Home>(entity);
        home.position = position;
        registry.emplace<Comps::Ant>(entity);
        registry.emplace<Comps::Alive>(entity);
        registry.emplace<Comps::Newborn>(entity);
        return entity;
	}

    entt::entity createFood(entt::registry& registry, mathfu::vec2 position)
    {
        const auto entity = registry.create();
        Comps::Trans& trans = registry.emplace<Comps::Trans>(entity);
        trans.position = position;
        auto& spriteRender = registry.emplace<Comps::SpriteRender>(entity);
        spriteRender.setTexture(Assets::get("assets/marker.png"));
        spriteRender.desiredDimensions = { 15 , 15 };
        spriteRender.tint = GREEN;

        registry.emplace<Comps::Food>(entity);
        registry.emplace<Comps::StaticSpatialRegister>(entity);
        return entity;
    }

    entt::entity createPheromone(entt::registry& registry, mathfu::vec2 position, Comps::PheromoneType type)
    {
        const auto entity = registry.create();
        Comps::Trans& trans = registry.emplace<Comps::Trans>(entity);
        trans.position = position;
        auto& spriteRender = registry.emplace<Comps::SpriteRender>(entity);
        spriteRender.setTexture(Assets::get("assets/marker.png"));
        spriteRender.desiredDimensions = { 10 , 10 };
        spriteRender.tint = BLUE;

        registry.emplace<Comps::Pheromone>(entity, type);
        registry.emplace<Comps::StaticSpatialRegister>(entity);
        return entity;
    }
  
}

