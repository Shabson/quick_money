#include "Player.h"

Player::Player(float x, float y,
    sf::Keyboard::Key left,
    sf::Keyboard::Key right,
    sf::Keyboard::Key up,
    sf::Keyboard::Key down)
{
    body.setSize(sf::Vector2f(80.f, 120.f));
    body.setFillColor(sf::Color::Green);
    body.setPosition(x, y);

    speed = 8.f;
    velocityY = 0.f;

    isGrounded = false;

    leftKey = left;
    rightKey = right;
    upKey = up;
    downKey = down;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(leftKey))
    {
        body.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(rightKey))
    {
        body.move(speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(upKey))
    {
        body.move(0.f, -speed);
    }

    if (sf::Keyboard::isKeyPressed(downKey))
    {
        body.move(0.f, speed);
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::Vector2f Player::getPosition() const
{
    return body.getPosition();
}

sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
}

void Player::update(std::vector<Platform>& platforms)
{
    // gravity
    velocityY += 0.5f;

    body.move(0.f, velocityY);

    isGrounded = false;

    for (auto& platform : platforms)
    {
        if (body.getGlobalBounds().intersects(
            platform.getBounds()))
        {
            // gracz stoi na platformie
            body.setPosition(
                body.getPosition().x,
                platform.getBounds().top
                - body.getSize().y
            );

            velocityY = 0.f;

            isGrounded = true;
        }
    }
}