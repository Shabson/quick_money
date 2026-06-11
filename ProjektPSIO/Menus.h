#pragma once

#include "Player.h"
#include "Game.h"
#include "GameState.h"

void handleClassSelection(
    CharacterClass& p1Class,
    CharacterClass& p2Class,
    GameState& gameState,
    bool enterJustPressed
);

void handleMapSelection(
    int& selectedMap,
    GameState& gameState,
    bool enterJustPressed
);

void drawMapSelectionMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    int selectedMap
);

void drawClassSelectionMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    CharacterClass p1Class,
    CharacterClass p2Class
);

std::string getClassName(
    CharacterClass characterClass
);

std::string getClassBonusText(
    CharacterClass characterClass
);

void drawGameOverMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    int winner
);