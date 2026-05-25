#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class ParallaxLayer
{
private:
    sf::Texture texture;

    sf::Sprite sprite;

    float moveMultiplier;

public:
    ParallaxLayer(
        const std::string& texturePath,
        float multiplier,
        sf::Vector2u windowSize
    );

    void draw(
        sf::RenderWindow& window,
        const sf::View& camera
    );
};