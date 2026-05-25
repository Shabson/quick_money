#include "Map.h"
#include "Weapon.h"

Map::Map(sf::Vector2u windowSize)
{   
    this->windowSize = windowSize;

    loadMap1();
}

void Map::loadMap1()
{
    backgroundLayers.clear();

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-bg.png",
            0.02f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-montain-far.png",
            0.05f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-mountains.png",
            0.1f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-trees.png",
            0.2f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-foreground-trees.png",
            0.3f,
            windowSize
        )
    );

    platforms.clear();

    platforms.push_back(
        Platform(0.f, 950.f, 1920.f, 130.f)
    );

    platforms.push_back(
        Platform(300.f, 700.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(1200.f, 700.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(750.f, 500.f, 400.f, 40.f)
    );

    weapons.push_back(
        Weapon(900.f, 300.f)
    );
}

void Map::draw(sf::RenderWindow& window)
{
    for (auto& layer : backgroundLayers)
    {
        layer->draw(window);
    }

    for (auto& platform : platforms)
    {
        platform.draw(window);
    }

    for (auto& weapon : weapons)
    {
        weapon.draw(window);
    }

}

std::vector<Platform>& Map::getPlatforms()
{
    return platforms;
}

void Map::update(float cameraX)
{
    for (auto& layer : backgroundLayers)
    {
        layer->update(cameraX);
    }
}

