#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "ParallaxLayer.h"
#include "Weapon.h"
#include <memory>

class Map
{
private:
    std::vector<Platform> platforms;
    std::vector<sf::Vector2f> playerSpawns;
    std::vector<sf::Vector2f> weaponSpawns;
    std::vector<Weapon> weapons;
    std::vector<std::unique_ptr<ParallaxLayer>> backgroundLayers;
    sf::Vector2u windowSize;

public:
    Map(sf::Vector2u windowSize);

    void loadMap1();

    void draw(sf::RenderWindow& window);

    std::vector<Platform>& getPlatforms();

    void update(float cameraX);
};