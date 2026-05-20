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
    velocityX = 0.f;
    hp = 5;

    isGrounded = false;
    facingRight = true;

    attackCooldown = 0.f;

    leftKey = left;
    rightKey = right;
    upKey = up;
    downKey = down;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(leftKey))
    {
        velocityX = -speed;

        facingRight = false;
    }

    if (sf::Keyboard::isKeyPressed(rightKey))
    {
        velocityX = speed;

        facingRight = true;
    }

    if (
        sf::Keyboard::isKeyPressed(upKey)
        &&
        isGrounded
        )
    {
        velocityY = -15.f;

        isGrounded = false;
    }

    if (sf::Keyboard::isKeyPressed(downKey))
    {
        velocityY += 1.f;
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

int Player::getHp() const
{
    return hp;
}

void Player::update(std::vector<Platform>& platforms)
{

    if (attackCooldown > 0.f)
    {
        attackCooldown -= 1.f;
    }

    previousY = body.getPosition().y;

    velocityY += 0.5f;

    body.move(velocityX, velocityY);

    isGrounded = false;

    for (auto& platform : platforms)
    {
        sf::FloatRect playerBounds =
            body.getGlobalBounds();

        sf::FloatRect platformBounds =
            platform.getBounds();

        if (playerBounds.intersects(platformBounds))
        {
            // landing collision
            if (
                previousY + body.getSize().y
                <= platformBounds.top
                )
            {
                body.setPosition(
                    body.getPosition().x,
                    platformBounds.top
                    - body.getSize().y
                );

                velocityY = 0.f;

                isGrounded = true;
            }

            // head collision
            else if (
                previousY
                >= platformBounds.top
                + platformBounds.height
                )
            {
                body.setPosition(
                    body.getPosition().x,
                    platformBounds.top
                    + platformBounds.height
                );

                velocityY = 0.f;
            }

            // left collision
            else if (
                body.getPosition().x
                <
                platformBounds.left
                )
            {
                body.setPosition(
                    platformBounds.left
                    - body.getSize().x,
                    body.getPosition().y
                );
            }

            // right collision
            else
            {
                body.setPosition(
                    platformBounds.left
                    + platformBounds.width,
                    body.getPosition().y
                );
            }
        }
    }
    velocityX *= 0.85f;


}
void Player::resolveCollision(Player& otherPlayer)
{
    sf::FloatRect playerBounds =
        body.getGlobalBounds();

    sf::FloatRect otherBounds =
        otherPlayer.getBounds();

    sf::FloatRect overlap;

    if (playerBounds.intersects(otherBounds, overlap))
    {
        float pushAmount = overlap.width / 2.f;

        if (body.getPosition().x <
            otherPlayer.getPosition().x)
        {
            body.move(-pushAmount, 0.f);

            otherPlayer.body.move(pushAmount, 0.f);
        }
        else
        {
            body.move(pushAmount, 0.f);

            otherPlayer.body.move(-pushAmount, 0.f);
        }
    }
}

void Player::attack(Player& otherPlayer)
{
    if (attackCooldown > 0.f)
    {
        return;
    }

    sf::RectangleShape attackHitbox;

    attackHitbox.setSize(sf::Vector2f(60.f, 40.f));

    if (facingRight)
    {
        attackHitbox.setPosition(
            body.getPosition().x
            + body.getSize().x,

            body.getPosition().y + 30.f
        );
    }
    else
    {
        attackHitbox.setPosition(
            body.getPosition().x - 60.f,

            body.getPosition().y + 30.f
        );
    }

    if (
        attackHitbox.getGlobalBounds().intersects(
            otherPlayer.getBounds())
        )
    {
        otherPlayer.hp--;

        if (facingRight)
        {
            otherPlayer.velocityX = 15.f;
            otherPlayer.velocityY = -10.f;
        }
        else
        {
            otherPlayer.velocityX = -15.f;
            otherPlayer.velocityY = -10.f;
        }

        attackCooldown = 30.f;
    }
}