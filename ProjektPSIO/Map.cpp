#include "Map.h"

Map::Map()
{
    loadMap1();
}

void Map::loadMap1()
{
    platforms.clear();

    // ziemia
    platforms.push_back(Platform(0.f, 950.f, 1920.f, 130.f));

    // platformy
    platforms.push_back(Platform(300.f, 700.f, 300.f, 40.f));
    platforms.push_back(Platform(1200.f, 700.f, 300.f, 40.f));
    platforms.push_back(Platform(750.f, 500.f, 400.f, 40.f));
}

void Map::draw(sf::RenderWindow& window)
{
    for (auto& platform : platforms)
    {
        platform.draw(window);
    }
}

std::vector<Platform>& Map::getPlatforms()
{
    return platforms;
}