#include "Menus.h"

void handleClassSelection(
    CharacterClass& p1Class,
    CharacterClass& p2Class,
    GameState& gameState
)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        p1Class = CharacterClass::Warrior;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        p1Class = CharacterClass::GlassCannon;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        p1Class = CharacterClass::Thug;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        p1Class = CharacterClass::Ranger;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    {
        p2Class = CharacterClass::Warrior;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
    {
        p2Class = CharacterClass::GlassCannon;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
    {
        p2Class = CharacterClass::Thug;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
    {
        p2Class = CharacterClass::Ranger;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        gameState =
            GameState::MapSelection;
    }
}

void handleMapSelection(
    int& selectedMap,
    GameState& gameState
)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        selectedMap = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        selectedMap = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        selectedMap = 3;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        gameState =
            GameState::Playing;
    }
}