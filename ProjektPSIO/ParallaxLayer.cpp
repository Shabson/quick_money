#include "ParallaxLayer.h"

ParallaxLayer::ParallaxLayer(
    const std::string& texturePath,
    float multiplier,
    sf::Vector2u windowSize)
{
    texture.loadFromFile(texturePath);

    texture.setSmooth(false);

    sprite.setTexture(texture);

    moveMultiplier = multiplier;

    sf::Vector2u textureSize =
        texture.getSize();

    float scale = 7.f;

    if (textureSize.y != 0)
    {
        scale =
            static_cast<float>(windowSize.y)
            / textureSize.y;
    }

    sprite.setScale(scale, scale);
}

void ParallaxLayer::draw(
    sf::RenderWindow& window,
    const sf::View& camera
)
{
    sf::View parallaxView = camera;

    sf::Vector2f cameraCenter =
        camera.getCenter();

    float baseCenterX =
        camera.getSize().x / 2.f;

    float parallaxX =
        baseCenterX
        + (cameraCenter.x - baseCenterX)
        * moveMultiplier;

    parallaxView.setCenter(
        parallaxX,
        cameraCenter.y
    );

    window.setView(parallaxView);

    float spriteWidth =
        texture.getSize().x
        * sprite.getScale().x;

    for (int i = -2; i < 8; i++)
    {
        sprite.setPosition(
            i * spriteWidth,
            0.f
        );

        window.draw(sprite);
    }
}