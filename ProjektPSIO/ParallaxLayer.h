#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class ParallaxLayer
{
private:
    sf::Texture texture;

    sf::Sprite sprite;

    float moveMultiplier;

    bool repeat;

public:
    ParallaxLayer(
        const std::string& texturePath,
        float multiplier,
        sf::Vector2u windowSize,
        bool repeat = true
    );

    void draw(
        sf::RenderWindow& window,
        const sf::View& camera
    );
};