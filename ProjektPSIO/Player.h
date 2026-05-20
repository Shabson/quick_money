#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape body;
    float speed;

public:
    Player(float x, float y);

    void handleInput();
    void update();
    void draw(sf::RenderWindow& window);
};