    #include "Player.h"
    #include <utility>


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

            velocityY = 0.f;
            velocityX = 0.f;

		    jumpHeld = false;
		    previousY = y;
     
            hasWeapon = false;
            playerClass = chosenClass;

            isGrounded = false;
            facingRight = true;
            jumpLeft = 2;

            attackCooldown = 0.f;
            dropCooldown = 0;

            leftKey = left;
            rightKey = right;
            upKey = up;
            downKey = down;

            speedMultiplier = 1.f;
            damageMultiplier = 1.f;
            rangedDamageMultiplier = 1.f;
            cooldownMultiplier = 1.f;
            hpMultiplier = 1.f;

            dodgeChance = 0.f;

            animationFrame = 0;
            animationTimer = 0;
            dodgeFlashTimer = 0;

            attackAnimationPlaying = false;
            attackAnimationTimer = 0;

            switch (playerClass)
            {
            case CharacterClass::Warrior:

                hpMultiplier = 1.35f;
                damageMultiplier = 0.9f;
                speedMultiplier = 0.95f;

                break;

            case CharacterClass::Berserker:

                hpMultiplier = 0.7f;
                damageMultiplier = 1.25f;
                cooldownMultiplier = 0.75f;

                break;

            case CharacterClass::Thug:

                speedMultiplier = 1.15f;
                dodgeChance = 0.25f;

                break;

            case CharacterClass::Ranger:

                hpMultiplier = 0.9f;
                rangedDamageMultiplier = 2.0f;
                cooldownMultiplier = 0.90f;

                break;
            }

            sprites.loadClass(
                chosenClass
            );

            speed = 8.0f * speedMultiplier;
            hp = 50.f * hpMultiplier; 
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
                jumpLeft > 0
                &&
			    !jumpHeld
                )
            {
                velocityY = -15.f;

                jumpLeft--;
            
			    jumpHeld = true;

                isGrounded = false;
		    }
		    else if (!sf::Keyboard::isKeyPressed(upKey))
		    {
			    jumpHeld = false;
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
            if (dodgeFlashTimer > 0)
            {
                sprites.setColor(
                    sf::Color(
                        255,
                        255,
                        100
                    )
                );
            }
            else
            {
                sprites.setColor(
                    sf::Color::White
                );
            }
            sprites.draw(window);

            if (hasWeapon)
            {
                currentWeapon->update();
                currentWeapon->draw(
                    window
                );
            }
        }

        void Player::drawCooldownBar(sf::RenderWindow& window, sf::Font& font)
        {
            float width = 50.f;
            float height = 6.f;

            float maxCooldown;

            if (hasWeapon)
            {
                maxCooldown =
                    currentWeapon->getAttackCooldown() * cooldownMultiplier;
            }
            else
            {
                maxCooldown = 20.f * cooldownMultiplier;
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

            Pistol* pistol =
                dynamic_cast<Pistol*>(
                    currentWeapon.get()
                    );

            if (pistol)
            {
                sf::Text ammoText;

                ammoText.setFont(font);
                ammoText.setCharacterSize(40);

                ammoText.setString(
                    std::to_string(
                        pistol->getAmmo()
                    )
                );

                ammoText.setPosition(
                    body.getPosition().x +32.f,
                    body.getPosition().y + 120.f
                );

			    ammoText.setOutlineColor(sf::Color::Black);
                ammoText.setOutlineThickness(2.f);

                window.draw(ammoText);
            }

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

        float Player::getHp() const
        {
            return hp;
        }

        bool Player::getHasWeapon() const
        {
            return hasWeapon;
        }

        const Weapon* Player::getCurrentWeapon() const
        {
            return currentWeapon.get();
        }

        void Player::setCurrentWeapon(
            std::unique_ptr<Weapon> weapon
        )
        {
            currentWeapon = std::move(weapon);

            if (currentWeapon)
            {
                currentWeapon->setDropped(false);
            }

            hasWeapon = currentWeapon != nullptr;
        }

        std::unique_ptr<Weapon> Player::takeCurrentWeapon()
        {
            hasWeapon = false;

            return std::move(currentWeapon);
        }

        int Player::getDeaths() const
        {
            return deaths;
        }

        void Player::addDeath()
        {
            deaths++;
        }

        bool Player::takeDamage(
            float damage
        )
        {
            if (
                static_cast<float>(rand())
                / RAND_MAX
                < dodgeChance
                )
            {
                dodgeFlashTimer = 20;
                return false;
            }

            hp -= damage;

            hp = std::max(
                0.f,
                hp
            );
            return true;
        }

        void Player::update(std::vector<Platform>& platforms)
        {

            if (dropCooldown > 0)
            {
                dropCooldown--;
            }

            if (dodgeFlashTimer > 0)
            {
                dodgeFlashTimer--;
            }

            bool wasGrounded = isGrounded;
            isGrounded = false;

            if (isGrounded)
            {
                jumpLeft = 1;
            }

            if (attackCooldown > 0.f)   
            {
                attackCooldown -= 1.f;
            }

            if (attackAnimationPlaying)
            {
                float animationLength =
                    hasWeapon
                    ? currentWeapon->getAttackCooldown() * 0.4f
                    : 8.f;

                attackAnimationTimer++;

                if (attackAnimationTimer >= animationLength)
                {
                    attackAnimationPlaying = false;
                    attackAnimationTimer = 0;
                }
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
                        jumpLeft = 2;
                    }
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
            velocityX *= 0.9f;


            float animationLength =
                hasWeapon
                ? currentWeapon->getAttackCooldown() * 0.4f
                : 8.f;

            float half =
                animationLength / 2.f;

            if (hasWeapon)
            {
                currentWeapon->setFacingRight(
                    facingRight
                );

                float positionOffset = 0.f;

                float YOffset = 0.f;

                float weaponAngle =
                    facingRight
                    ? 20.f
                    : -20.f;

                if (
                    attackAnimationPlaying
                    &&
                    currentWeapon->getAnimationType()
                    == WeaponAnimationType::Swing
                    )
                {
                    if (attackAnimationTimer < half)
                    {
                        float progress =
                            attackAnimationTimer / half;

                        if (facingRight)
                        {
                            weaponAngle =
                                20.f + progress * 100.f;
                        }
                        else
                        {
                            weaponAngle =
                                -20.f - progress * 100.f;
                        }
                    }
                    else
                    {
                        float progress =
                            (attackAnimationTimer - half)
                            / half;

                        if (facingRight)
                        {
                            weaponAngle =
                                120.f - progress * 100.f;
                        }
                        else
                        {
                            weaponAngle =
                                -120.f + progress * 100.f;
                        }
                    }
                }
                else if (
                    attackAnimationPlaying
                    &&
                    currentWeapon->getAnimationType()
                    == WeaponAnimationType::Thrust
                    )
                {
                    weaponAngle =
                        facingRight
                        ? 45.f
                        : -45.f;

                    YOffset = 25.f;

                    if (attackAnimationTimer < half)
                    {
                        positionOffset =
                            attackAnimationTimer
                            / half
                            * 40.f;
                    }
                    else
                    {
                        positionOffset =
                            (animationLength
                                - attackAnimationTimer)
                            / half
                            * 40.f;
                    }
                }
                else if (
                    attackAnimationPlaying
                    &&
                    currentWeapon->getAnimationType()
                    == WeaponAnimationType::Recoil
                    )
                {
                    weaponAngle = 0.f;

                    float progress =
                        attackAnimationTimer
                        / animationLength;

                    positionOffset =
                        (1.f - progress)
                        * 15.f;
                }

                currentWeapon->setRotation(
                    weaponAngle
                );

                sf::Vector2f hitboxSize =
                    currentWeapon->getHitboxSize();



                if (facingRight)
                {
                    currentWeapon->setPosition(
                        body.getPosition().x
                        + body.getSize().x
                        - 4.f
                        + positionOffset,

                        body.getPosition().y + 65.f - YOffset
                    );
                }
                else
                {
                    currentWeapon->setPosition(
                        body.getPosition().x
                        + 4.f
                        - positionOffset,

					    body.getPosition().y + 65.f - YOffset
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
            if (
                hasWeapon
                &&
                currentWeapon->shouldDespawn()
                )
            {
                currentWeapon.reset();
                hasWeapon = false;
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

            attackAnimationPlaying = true;
            attackAnimationTimer = 0;

            sf::RectangleShape attackHitbox;

            attackHitbox.setSize(
                hasWeapon
                ? currentWeapon->getHitboxSize()
                : sf::Vector2f(60.f, 40.f)
            );

            attackHitbox.setPosition(
                facingRight
                ? body.getPosition().x + body.getSize().x
                : body.getPosition().x - attackHitbox.getSize().x,

                body.getPosition().y + 30.f
            );

            if (hasWeapon)
            {
                attackCooldown = currentWeapon->getAttackCooldown() * cooldownMultiplier;
            }
            else
            {
				attackCooldown = 25.f * cooldownMultiplier;
            }

            if (
                attackHitbox.getGlobalBounds().intersects(
                    otherPlayer.getBounds()
                )
                )
            {
                if (
                    otherPlayer.takeDamage(
                        (
                            hasWeapon
                            ? currentWeapon->getDamage()
                            : 1.f
                            )
                        * damageMultiplier
                    )
                    )
                {
                    otherPlayer.applyKnockback(
                        hasWeapon
                        ? currentWeapon->getKnockback()
                        : 15.f,
                        -5.f,
                        facingRight
                    );
                }
            }
        }
            
        void Player::respawn(float x, float y)
        {
            body.setPosition(x, y);

            velocityX = 0.f;
            velocityY = 0.f;

            hp = 50.f * hpMultiplier;

            hasWeapon = false;

            currentWeapon.reset();
        }

        float Player::getMaxHp() const
        {
            return maxHp;
        }

        bool Player::canAttack() const
        {
            return attackCooldown <= 0.f;
        }

        void Player::startAttackCooldown()
        {
            if (hasWeapon)
            {
                attackCooldown =
                    currentWeapon->getAttackCooldown() * cooldownMultiplier;
            }
            else
            {
                attackCooldown = 15.f * cooldownMultiplier;
            }
        }

        void Player::useAmmo()
        {
            Pistol* pistol =
                dynamic_cast<Pistol*>(
                    currentWeapon.get()
                    );

            if (!pistol)
            {
                return;
            }

            pistol->useAmmo();

            attackAnimationPlaying = true;
            attackAnimationTimer = 0;

            if (pistol->getAmmo() <= 0)
            {
                currentWeapon.reset();
                hasWeapon = false;
            }
        }

        int Player::getAmmo() const
        {
            Pistol* pistol =
                dynamic_cast<Pistol*>(
                    currentWeapon.get()
                    );

            if (pistol)
            {
                return pistol->getAmmo();
            }

            return -1;
        }

        bool Player::canDropWeapon() const
        {
            return dropCooldown <= 0;
        }

        void Player::startDropCooldown()
        {
            dropCooldown = 30.f;
        }

        void Player::applyKnockback(
            float baseKnockbackX,
            float baseKnockbackY,
            bool fromRight
        )
        {
            float hpPercent =
                static_cast<float>(hp)
                / maxHp;

            float multiplier =
                1.f
                / std::max(
                    0.1f,
                    hpPercent
                );

            velocityX =
                fromRight
                ? baseKnockbackX * multiplier
                : -baseKnockbackX * multiplier;

            velocityY =
                baseKnockbackY * multiplier;
        }

		float Player::getRangedDamageMultiplier() const
		{
			return rangedDamageMultiplier;
		}