#include "Platform.h"

Platform::Platform(float x, float y, float width, float height)
{
    body.setPosition(x, y);
    body.setSize(sf::Vector2f(width, height));
    body.setFillColor(sf::Color::White);
}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::RectangleShape& Platform::getBody()
{
    return body;
}