#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
private:
    sf::RectangleShape body;

public:
    Platform(float x, float y, float width, float height);

    void draw(sf::RenderWindow& window);

    sf::RectangleShape& getBody();
};