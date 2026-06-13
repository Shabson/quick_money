#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Platform.h"
#include "Weapon.h"
#include "CharacterSprites.h"
#include "CharacterClass.h"


class Player
{
private:
    sf::RectangleShape body;
    float speed;

    float previousY;
    float velocityY;

    float velocityX;

    bool isGrounded;
    int jumpLeft;
    bool jumpHeld;
    bool facingRight;

    float attackCooldown;

    int deaths;
    int hp;
	int maxHp;

    std::unique_ptr<Weapon> currentWeapon;
    bool hasWeapon;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;

    sf::RectangleShape weaponVisual;
    sf::RectangleShape weaponHitboxPreview;

    CharacterClass playerClass;

    float damageMultiplier;
    float speedMultiplier;
    float cooldownMultiplier;
    float hpMultiplier;

    float dodgeChance;

    CharacterSprites sprites;
    int animationFrame;
    int animationTimer;

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
	int getMaxHp() const;
    bool getHasWeapon() const;
    void respawn(float x, float y);
    void drawCooldownBar(sf::RenderWindow& window);
    const Weapon* getCurrentWeapon() const;
    void setCurrentWeapon(std::unique_ptr<Weapon> weapon);
    std::unique_ptr<Weapon> takeCurrentWeapon();
    void dropWeapon();
    int getDeaths() const;
    void addDeath();

};
