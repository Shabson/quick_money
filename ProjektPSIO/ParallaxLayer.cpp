#include "ParallaxLayer.h"

ParallaxLayer::ParallaxLayer(
    const std::string& texturePath,
    float multiplier)
{
    texture.loadFromFile(texturePath);

    sprite.setTexture(texture);

    moveMultiplier = multiplier;
}

void ParallaxLayer::update(float cameraX)
{
    sprite.setPosition(-cameraX * moveMultiplier, 0.f);
}

void ParallaxLayer::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}