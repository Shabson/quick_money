#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Weapon
{
protected:
    sf::RectangleShape body;

    float damage;
    float attackCooldown;
    float knockback;

    sf::Vector2f hitboxSize;

    Weapon(
        float x,
        float y,
        float damage,
        float attackCooldown,
        float knockback,
        sf::Vector2f hitboxSize,
        sf::Color color
    );

public:
    virtual ~Weapon() = default;

    virtual std::unique_ptr<Weapon> clone() const = 0;
    virtual std::string getName() const = 0;

    virtual void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    float getDamage() const;
    float getAttackCooldown() const;
    float getKnockback() const;
    sf::Vector2f getHitboxSize() const;

    void setPosition(float x, float y);

    sf::Vector2f getPosition() const;

    bool dropped;
    int droppedTimer;

    void setDropped(
        bool value
    );

    bool isDropped() const;

    void update();

    bool shouldDespawn() const;
};

class MeleeWeapon : public Weapon
{
protected:
    MeleeWeapon(
        float x,
        float y,
        float damage,
        float attackCooldown,
        float knockback,
        sf::Vector2f hitboxSize,
        sf::Color color
    );
};

class Sword : public MeleeWeapon
{
public:
    Sword(float x, float y);

    std::unique_ptr<Weapon> clone() const override;
    std::string getName() const override;
};

class Katana : public MeleeWeapon
{
public:
    Katana(float x, float y);

    std::unique_ptr<Weapon> clone() const override;
    std::string getName() const override;
};

class Club : public MeleeWeapon
{
public:
    Club(float x, float y);

    std::unique_ptr<Weapon> clone() const override;
    std::string getName() const override;
};

class Spear : public MeleeWeapon
{
public:
    Spear(float x, float y);

    std::unique_ptr<Weapon> clone() const override;
    std::string getName() const override;
};

class Pistol : public Weapon
{
public:
    Pistol(float x, float y);

    std::unique_ptr<Weapon> clone() const override;
    std::string getName() const override;
};
