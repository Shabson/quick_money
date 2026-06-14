#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

void drawHUD(
    sf::RenderWindow& window,
    sf::Font& font,
	const Player& player1,
	const Player& player2
);