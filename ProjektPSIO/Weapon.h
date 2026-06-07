#pragma once

#include <SFML/Graphics.hpp>

enum class WeaponType
{
    Sword,
    Katana,
    Bat,
    Spear
};

class Weapon
{
private:
    sf::RectangleShape body;

    WeaponType type;

    float damage;
    float attackCooldown;
    float knockback;

    sf::Vector2f hitboxSize;

public:

    Weapon();

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    float getDamage() const;
    float getAttackCooldown() const;
    float getKnockback() const;
    sf::Vector2f getHitboxSize() const;
    WeaponType getType() const;

    Weapon(WeaponType weaponType, float x, float y);
    std::string getName() const;
    void setPosition(float x, float y);

    sf::Vector2f getPosition() const;
};