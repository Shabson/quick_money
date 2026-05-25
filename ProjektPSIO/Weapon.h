#pragma once

#include <SFML/Graphics.hpp>

class Weapon
{
private:
    sf::RectangleShape body;

public:
    Weapon(float x, float y);

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};