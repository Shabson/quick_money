#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Menus.h"
#include "GameState.h"
#include "pocisk.h"

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
    int winner;

    sf::Font font;

    Map* map;
    std::vector<Pocisk> pociski;

    bool enterPressedLastFrame;

public:

    Game(
        sf::RenderWindow& window
    );

    void run();
    void resetCamera();
};