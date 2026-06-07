#include "Weapon.h"


void Weapon::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::FloatRect Weapon::getBounds() const
{
    return body.getGlobalBounds();
}
Weapon::Weapon()
{
    type = WeaponType::Sword;

    damage = 0.f;
    attackCooldown = 15.f;
    knockback = 0.f;

    hitboxSize = sf::Vector2f(0.f, 0.f);

    body.setSize(
        sf::Vector2f(0.f, 0.f)
    );
}

Weapon::Weapon(WeaponType weaponType, float x, float y)
{
    type = weaponType;
    body.setSize(sf::Vector2f(80.f, 20.f));

    body.setPosition(x, y);

    switch (type)
    {
    case WeaponType::Sword:

        damage = 2.f;
        attackCooldown = 25.f;
        knockback = 18.f;
        hitboxSize = sf::Vector2f(100.f, 40.f);

        body.setFillColor(sf::Color::White);

        break;

    case WeaponType::Katana:

        damage = 1.f;
        attackCooldown = 10.f;
        knockback = 12.f;
        hitboxSize = sf::Vector2f(140.f, 30.f);

        body.setFillColor(sf::Color::Cyan);

        break;

    case WeaponType::Bat:

        damage = 3.f;
        attackCooldown = 40.f;
        knockback = 35.f;
        hitboxSize = sf::Vector2f(90.f, 50.f);

        body.setFillColor(sf::Color(139, 69, 19));

        break;

    case WeaponType::Spear:

        damage = 2.f;
        attackCooldown = 30.f;
        knockback = 20.f;
        hitboxSize = sf::Vector2f(180.f, 25.f);

        body.setFillColor(sf::Color::Yellow);

        break;
    }
}

float Weapon::getDamage() const
{
    return damage;
}

float Weapon::getAttackCooldown() const
{
    return attackCooldown;
}

float Weapon::getKnockback() const
{
    return knockback;
}

sf::Vector2f Weapon::getHitboxSize() const
{
    return hitboxSize;
}

WeaponType Weapon::getType() const
{
    return type;
}

std::string Weapon::getName() const
{
    switch (type)
    {
    case WeaponType::Sword:
        return "Sword";

    case WeaponType::Katana:
        return "Katana";

    case WeaponType::Bat:
        return "Bat";

    case WeaponType::Spear:
        return "Spear";
    }

    return "Unknown";
}

void Weapon::setPosition(
    float x,
    float y
)
{
    body.setPosition(x, y);
}

sf::Vector2f Weapon::getPosition() const
{
    return body.getPosition();
}