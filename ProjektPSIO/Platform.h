#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
private:
    sf::RectangleShape body;
   

public:
    Platform(float x, float y, float width, const sf::Texture& texture);

    void draw(sf::RenderWindow& window);    

    sf::RectangleShape& getBody();
    sf::FloatRect getBounds() const;
};