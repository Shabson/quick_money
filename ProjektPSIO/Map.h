#pragma once
#include <vector>
#include <SFML/Graphics.hpp>    
#include "Platform.h"

class Map
{
private:
    std::vector<Platform> platforms;
    std::vector<sf::Vector2f> playerSpawns;
    std::vector<sf::Vector2f> weaponSpawns;

    sf::Sprite background;
public:
    Map();

    void loadMap1();

    void draw(sf::RenderWindow& window);

    std::vector<Platform>& getPlatforms();
};