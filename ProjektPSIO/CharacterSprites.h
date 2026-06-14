#pragma once

#include "CharacterClass.h"
#include <SFML/Graphics.hpp>
#include <vector>

class CharacterSprites
{
private:

    sf::Texture bodyTexture;
    sf::Texture headTexture;
    sf::Texture torsoTexture;
    sf::Texture legsTexture;
    sf::Texture feetTexture;
    sf::Texture armsTexture;

    sf::Sprite bodySprite;
    sf::Sprite headSprite;
    sf::Sprite torsoSprite;
    sf::Sprite legsSprite;
    sf::Sprite feetSprite;
    sf::Sprite armsSprite;

    int currentFrame;

    std::vector<sf::Sprite*> sprites;

public:

    CharacterSprites();

    void loadClass(
        CharacterClass characterClass
    );

    void setFrame(
        int frame,
        int row
    );

    void setPosition(
        float x,
        float y
    );

    void setFacingRight(
        bool facingRight
    );

    void setColor(
        const sf::Color& color
    );

    void loadBody(
        const std::string& path
    );

    void loadHead(
        const std::string& path
    );

    void loadTorso(
        const std::string& path
    );

    void loadLegs(
        const std::string& path
    );

    void loadFeet(
        const std::string& path
    );

    void loadArms(
        const std::string& path
    );

    void draw(
        sf::RenderWindow& window
    );
};