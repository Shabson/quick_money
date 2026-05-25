#include "ParallaxLayer.h"
#include <algorithm>

ParallaxLayer::ParallaxLayer(
    const std::string& texturePath,
    float multiplier,
    sf::Vector2u windowSize,
    bool repeat)
{
    texture.loadFromFile(texturePath);

    texture.setSmooth(false);

    sprite.setTexture(texture);

    moveMultiplier = multiplier;

    this->repeat = repeat;

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

    float viewWidth =
        camera.getSize().x;

    float viewHeight =
        camera.getSize().y;

    float textureWidth =
        texture.getSize().x;

    float textureHeight =
        texture.getSize().y;

    float scaleX =
        viewWidth / textureWidth;

    float scaleY =
        viewHeight / textureHeight;

    float scale =
        std::max(scaleX, scaleY);

    sprite.setScale(scale, scale);

    float spriteWidth =
        textureWidth * scale;

    float topY =
        cameraCenter.y
        - viewHeight / 2.f;

    if (!repeat)
    {
        sprite.setPosition(
            parallaxX - spriteWidth / 2.f,
            topY
        );

        window.draw(sprite);

        return;
    }

    for (int i = -2; i < 8; i++)
    {
        sprite.setPosition(
            i * spriteWidth,
            topY
        );

        window.draw(sprite);
    }
}