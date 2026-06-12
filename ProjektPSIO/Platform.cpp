#include "Platform.h"

Platform::Platform(float x, float y, float width, const sf::Texture& texture)
{
    body.setPosition(x, y);
    body.setSize(sf::Vector2f(width*48.f, 48.f));
    body.setTexture(&texture);

    body.setTextureRect(
        sf::IntRect(
            0,
            0,
            static_cast<int>(width * 48.f),
            static_cast<int>(48.f)
        )
    );
}



void Platform::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::RectangleShape& Platform::getBody()
{
    return body;
}

sf::FloatRect Platform::getBounds() const
{
    return body.getGlobalBounds();
}