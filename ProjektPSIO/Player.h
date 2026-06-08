#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Weapon.h"

enum class CharacterClass
{
    Warrior,
    GlassCannon,
    Thug,
    Ranger
};

class Player
{
private:
    sf::RectangleShape body;
    float speed;

    float previousY;
    float velocityY;

    float velocityX;

    bool isGrounded;
    bool facingRight;

    float attackCooldown;

    int deaths;
    int hp;

    Weapon currentWeapon;
    bool hasWeapon;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;

    sf::RectangleShape weaponVisual;

    CharacterClass playerClass;

    float damageMultiplier;
    float speedMultiplier;
    float cooldownMultiplier;
    float hpMultiplier;

    float dodgeChance;

public:
    Player(
        float x,
        float y,

        CharacterClass chosenClass,

        sf::Keyboard::Key left,
        sf::Keyboard::Key right,
        sf::Keyboard::Key up,
        sf::Keyboard::Key down
    );

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    bool isFacingRight() const;

    void handleInput();
    void update(std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window);
    void resolveCollision(Player& otherPlayer);
    void attack(Player& otherPlayer);
    int getHp() const;
    bool getHasWeapon() const;
    void respawn(float x, float y);
    void drawCooldownBar(sf::RenderWindow& window);
    Weapon getCurrentWeapon() const;
    void setCurrentWeapon(const Weapon& weapon);
    void dropWeapon();
    int getDeaths() const;
    void addDeath();

};