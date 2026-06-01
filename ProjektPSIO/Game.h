#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Menus.h"
#include "GameState.h"


class Game
{
private:

    sf::RenderWindow& window;

    sf::View camera;

    float currentZoom;

    GameState gameState;

    CharacterClass p1Class;
    CharacterClass p2Class;

    int selectedMap;

    Player* player1;
    Player* player2;

    Map* map;

public:

    Game(
        sf::RenderWindow& window
    );

    void run();
};