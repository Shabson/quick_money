#include "pocisk.h"


Pocisk::Pocisk(
    float x,
    float y,
    bool goingRight
)
{
    body.setSize(
        sf::Vector2f(20.f, 8.f)
    );

    body.setFillColor(
        sf::Color::Yellow
    );

    body.setPosition(x, y);

    velocityX =
        goingRight
        ? 20.f
        : -20.f;
}

void Pocisk::update()
{
    body.move(
        velocityX,
        0.f
    );
}

void Pocisk::draw(
    sf::RenderWindow& window
)
{
    window.draw(body);
}

sf::FloatRect Pocisk::getBounds() const
{
    return body.getGlobalBounds();
}