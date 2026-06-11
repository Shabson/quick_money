    #include "Player.h"

Player::Player(float x, float y, CharacterClass chosenClass,
        sf::Keyboard::Key left,
        sf::Keyboard::Key right,
        sf::Keyboard::Key up,
        sf::Keyboard::Key down)
    {
        body.setSize(
            sf::Vector2f(
                40.f,
                90.f
            )
        );

        body.setPosition(x, y);

        body.setFillColor(
            sf::Color(255, 0, 0, 60)
        ); // drawing hitboxa

        velocityY = 0.f;
        velocityX = 0.f;
     
        hasWeapon = false;
        playerClass = chosenClass;

        isGrounded = false;
        facingRight = true;

        attackCooldown = 0.f;

        leftKey = left;
        rightKey = right;
        upKey = up;
        downKey = down;

        speedMultiplier = 1.f;
        damageMultiplier = 1.f;
        cooldownMultiplier = 1.f;
        hpMultiplier = 1.f;

        dodgeChance = 0.f;

        animationFrame = 0;
        animationTimer = 0;

        weaponVisual.setSize(
            sf::Vector2f(60.f, 15.f)
        );

        weaponVisual.setFillColor(
            sf::Color::Red
        );

        switch (playerClass)
        {
        case CharacterClass::Warrior:

            hpMultiplier = 1.2f;
            damageMultiplier = 1.1f;
            speedMultiplier = 0.95f;
            cooldownMultiplier = 1.f;

            dodgeChance = 0.f;

            break;

        case CharacterClass::GlassCannon:

            hpMultiplier = 0.7f;
            damageMultiplier = 1.25f;
            speedMultiplier = 1.05f;
            cooldownMultiplier = 0.9f;

            dodgeChance = 0.f;

            break;

        case CharacterClass::Thug:

            hpMultiplier = 1.f;
            damageMultiplier = 1.f;
            speedMultiplier = 1.15f;
            cooldownMultiplier = 1.f;

            dodgeChance = 0.15f;

            break;

        case CharacterClass::Ranger:

            hpMultiplier = 0.9f;
            damageMultiplier = 1.f;
            speedMultiplier = 1.08f;
            cooldownMultiplier = 0.95f;

            dodgeChance = 0.05f;

            break;
        }

        sprites.loadClass(
            chosenClass
        );

        speed = 8.0f * speedMultiplier;
        hp = 50 * hpMultiplier; 
        maxHp = hp;

        deaths = 0;
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
        sprites.setPosition(
            body.getPosition().x,
            body.getPosition().y
        );

		sprites.setFacingRight(
			facingRight
		);

        sprites.setFrame(
            animationFrame,
            3
        );

        sprites.draw(window);

        if (hasWeapon)
        {
            window.draw(weaponVisual);
        }
       // window.draw(body); //drawing hitboxa
    }

    void Player::drawCooldownBar(sf::RenderWindow& window)
    {
        float width = 50.f;
        float height = 6.f;

        float maxCooldown;

        if (hasWeapon)
        {
            maxCooldown =
                currentWeapon.getAttackCooldown();
        }
        else
        {
            maxCooldown = 15.f;
        }

        float ratio = attackCooldown / maxCooldown;

        if (ratio < 0.f)
        {
            ratio = 0.f;
        }

        sf::RectangleShape background;

        background.setSize(
            sf::Vector2f(width, height)
        );

        background.setFillColor(
            sf::Color(70, 70, 70)
        );

        background.setPosition(
            body.getPosition().x
            + body.getSize().x / 2.f
            - width / 2.f,

            body.getPosition().y
            + body.getSize().y
            + 10.f
        );

        sf::RectangleShape bar;

        bar.setSize(
            sf::Vector2f(width * ratio, height)
        );

        bar.setFillColor(
            sf::Color(210, 210, 210)
        );

        bar.setPosition(
            body.getPosition().x
            + body.getSize().x / 2.f
            - width / 2.f,

            body.getPosition().y
            + body.getSize().y
            + 10.f
        );

        window.draw(background);
        window.draw(bar);
    }

    sf::Vector2f Player::getPosition() const
    {
        return body.getPosition();
    }

    sf::FloatRect Player::getBounds() const
    {
        return body.getGlobalBounds();
    }

    bool Player::isFacingRight() const
    {
        return facingRight;
    }

    int Player::getHp() const
    {
        return hp;
    }

    bool Player::getHasWeapon() const
    {
        return hasWeapon;
    }

    Weapon Player::getCurrentWeapon() const
    {
        return currentWeapon;
    }

    void Player::setCurrentWeapon(
        const Weapon& weapon
    )
    {
        currentWeapon = weapon;

        hasWeapon = true;
    }

    int Player::getDeaths() const
    {
        return deaths;
    }

    void Player::addDeath()
    {
        deaths++;
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

        if (hasWeapon)
        {
            if (facingRight)
            {
                weaponVisual.setPosition(
                    body.getPosition().x
                    + body.getSize().x,

                    body.getPosition().y + 40.f
                );
            }
            else
            {
                weaponVisual.setPosition(
                    body.getPosition().x - 60.f,

                    body.getPosition().y + 40.f
                );
            }
        }

        animationTimer++;

        if (abs(velocityX) > 0.5f)
        {
            if (animationTimer > 4)
            {
                animationTimer = 0;

                animationFrame++;

                if (animationFrame > 8)
                {
                    animationFrame = 1;
                }
            }
        }
        else
        {
            animationFrame = 0;
        }

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
        
            if (overlap.width < overlap.height)
            {
                float pushAmount =
                    overlap.width / 2.f;

                if (
                    body.getPosition().x
                    <
                    otherPlayer.getPosition().x
                    )
                {
                    body.move(-pushAmount, 0.f);

                    otherPlayer.body.move(
                        pushAmount,
                        0.f
                    );
                }
                else
                {
                    body.move(pushAmount, 0.f);

                    otherPlayer.body.move(
                        -pushAmount,
                        0.f
                    );
                }
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

        if (hasWeapon)
        {
            attackHitbox.setSize(
                currentWeapon.getHitboxSize()
            );
        }
        else
        {
            attackHitbox.setSize(
                sf::Vector2f(60.f, 40.f)
            );
        }

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
                body.getPosition().x
                - attackHitbox.getSize().x,

                body.getPosition().y + 30.f
            );
        
        }

        if (hasWeapon)
        {
            attackCooldown =
                currentWeapon.getAttackCooldown();
        }
        else
        {
            attackCooldown = 15.f;
        }

        if (
            attackHitbox.getGlobalBounds().intersects(
                otherPlayer.getBounds())
            )
        {
            if (hasWeapon)
            {
                otherPlayer.hp -=
                    currentWeapon.getDamage()
                    * damageMultiplier;
            }
            else
            {
                otherPlayer.hp -= 1.0 * damageMultiplier;
            }

            if (facingRight)
            {
                if (hasWeapon)
                {
                    otherPlayer.velocityX =
                        currentWeapon.getKnockback();
                }
                else
                {
                    otherPlayer.velocityX = 15.f;
                }

                otherPlayer.velocityY = -10.f;
            }
            else
            {
                if (hasWeapon)
                {
                    otherPlayer.velocityX =
                        -currentWeapon.getKnockback();
                }
                else
                {
                    otherPlayer.velocityX = -15.f;
                }
                otherPlayer.velocityY = -10.f;
            }

       
        }
    }

    void Player::respawn(float x, float y)
    {
        body.setPosition(x, y);

        velocityX = 0.f;
        velocityY = 0.f;

        hp = 50 * hpMultiplier;

        hasWeapon = false;

        currentWeapon = Weapon();
    }

    void Player::dropWeapon()
    {
        hasWeapon = false;

        currentWeapon = Weapon();
    }

    int Player::getMaxHp() const
    {
        return maxHp;
    }