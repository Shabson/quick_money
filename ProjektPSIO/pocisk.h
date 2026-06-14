#pragma once

#include <SFML/Graphics.hpp>

class Pocisk
{
private:
    sf::RectangleShape body;

    float velocityX;

public:
    Pocisk(
        float x,
        float y,
        bool goingRight
    );

    void update();

    void draw(
        sf::RenderWindow& window
    );

    sf::FloatRect getBounds() const;
    float getX() const;

};