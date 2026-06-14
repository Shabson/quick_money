#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
#include "Menus.h"
#include "GameState.h"
#include "pocisk.h"
#include <memory>

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

    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    std::unique_ptr<Map> map;
    
    int winner;

    sf::Font font;

    std::vector<Pocisk> pociski;

    bool enterPressedLastFrame;

    bool fPressedLastFrame;
    bool rCtrlPressedLastFrame;

public:

    Game(
        sf::RenderWindow& window
    );

    void run();
    void resetCamera();
    void handleDeath(Player& player);

};