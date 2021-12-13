#include "SceneData.hpp"
#include "AssetManager.hpp"

Pheromone::Pheromone()
{
}

Pheromone::Pheromone(PheromoneType type) : type(type)
{
}

Texture2D Pheromone::getTexture()
{
    return Assets::get("assets/marker.png");
}

Color Pheromone::getColor()
{
    return GREEN;
}

Texture2D Wall::getTexture()
{
    return Assets::get("assets/marker.png");
}

Texture2D Food::getTexture()
{
    return Assets::get("assets/marker.png");
}

Color WorldGridEntry::getColor()
{
    return WHITE;
}
