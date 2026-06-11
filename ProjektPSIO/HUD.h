#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

void drawHUD(
    sf::RenderWindow& window,
    sf::Font& font,
    Player* player1,
    Player* player2
);