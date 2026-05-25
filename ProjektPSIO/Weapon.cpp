#include "Weapon.h"

Weapon::Weapon(float x, float y)
{
    body.setSize(
        sf::Vector2f(60.f, 20.f)
    );

    body.setFillColor(sf::Color::Red);

    body.setPosition(x, y);
}

void Weapon::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::FloatRect Weapon::getBounds() const
{
    return body.getGlobalBounds();
}