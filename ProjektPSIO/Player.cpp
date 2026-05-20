#include "Player.h"

Player::Player(float x, float y)
{
    body.setSize(sf::Vector2f(80.f, 120.f));
    body.setFillColor(sf::Color::Green);
    body.setPosition(x, y);

    speed = 8.f;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        body.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        body.move(speed, 0.f);
    }
}

void Player::update()
{

}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::Vector2f Player::getPosition() const
{
    return body.getPosition();
}
