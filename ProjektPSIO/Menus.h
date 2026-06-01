#pragma once

#include "Player.h"
#include "Game.h"
#include "GameState.h"

void handleClassSelection(
    CharacterClass& p1Class,
    CharacterClass& p2Class,
    GameState& gameState
);

void handleMapSelection(
    int& selectedMap,
    GameState& gameState
);