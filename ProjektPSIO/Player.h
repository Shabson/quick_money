#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Player
{
private:
    sf::RectangleShape body;
    float speed;

    float velocityY;

    bool isGrounded;

public:
    Player(float x, float y);

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    void handleInput();
    void update(std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window);
};