#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

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

    int hp;

    bool hasWeapon;

    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;

    sf::RectangleShape weaponVisual;

public:
    Player(
        float x,
        float y,

        sf::Keyboard::Key left,
        sf::Keyboard::Key right,
        sf::Keyboard::Key up,
        sf::Keyboard::Key down
    );

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    void handleInput();
    void update(std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window);
    void resolveCollision(Player& otherPlayer);
    void attack(Player& otherPlayer);
    int getHp() const;
    bool getHasWeapon() const;
    void setHasWeapon(bool value);
};