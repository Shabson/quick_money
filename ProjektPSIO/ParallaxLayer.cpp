#include "ParallaxLayer.h"
#include <iostream>

ParallaxLayer::ParallaxLayer(
    const std::string& texturePath,
    float multiplier,
    sf::Vector2u windowSize)
{
    texture.loadFromFile(texturePath);

    sprite.setTexture(texture);

    moveMultiplier = multiplier;

    sf::Vector2u textureSize = texture.getSize();


    float scale = 7.f;

    if (textureSize.y != 0)
    {
        scale =
            (float)windowSize.y / textureSize.y;
    }

    sprite.setScale(scale, scale);

    sprite.setPosition(0.f, 0.f);
}

void ParallaxLayer::draw(
    sf::RenderWindow& window,
    const sf::View& camera
)
{
    sf::View parallaxView = camera;

    sf::Vector2f cameraCenter =
        camera.getCenter();

    parallaxView.setCenter(
        cameraCenter.x * moveMultiplier
        + (1.f - moveMultiplier) * 640.f,
        cameraCenter.y
    );

    window.setView(parallaxView);

    window.draw(sprite);
}