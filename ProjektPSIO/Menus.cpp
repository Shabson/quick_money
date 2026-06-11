#include "Menus.h"

void handleClassSelection(
    CharacterClass& p1Class,
    CharacterClass& p2Class,
    GameState& gameState,
	bool enterJustPressed
)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        p1Class = CharacterClass::Warrior;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        p1Class = CharacterClass::Berserker;
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
        p2Class = CharacterClass::Berserker;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
    {
        p2Class = CharacterClass::Thug;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
    {
        p2Class = CharacterClass::Ranger;
    }

    if (enterJustPressed)
    {
        gameState =
            GameState::Playing;
    }
}

void handleMapSelection(
    int& selectedMap,
    GameState& gameState,
    bool enterJustPressed
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

    if (enterJustPressed)
    {
        gameState =
            GameState::ClassSelection;
    }
}

void drawMapSelectionMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    int selectedMap
)
{
    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);

    text.setString(
        "MAP SELECTION\n\n"
        "1 - Mountain Arena\n"
        "2 - Tower Arena\n"
        "3 - Long Arena\n\n"
        "Selected: " +
        std::to_string(selectedMap) +
        "\n\nPress ENTER"
    );

    text.setPosition(
        400.f,
        200.f
    );

    window.draw(text);
}

std::string getClassName(
    CharacterClass characterClass
)
{
    switch (characterClass)
    {
    case CharacterClass::Warrior:
        return "Warrior";

    case CharacterClass::Berserker:
        return "Berserker";

    case CharacterClass::Thug:
        return "Thug";

    case CharacterClass::Ranger:
        return "Ranger";
    }

    return "Unknown";
}

void drawClassSelectionMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    CharacterClass p1Class,
    CharacterClass p2Class
)
{
    sf::Text text;

    text.setFont(font);
    text.setFillColor(sf::Color::White);

    text.setCharacterSize(48);
    text.setString("CLASS SELECTION");
    text.setPosition(650.f, 50.f);
    window.draw(text);

    // PLAYER 1

    text.setCharacterSize(36);
    text.setString("PLAYER 1");
    text.setPosition(150.f, 180.f);
    window.draw(text);

    text.setCharacterSize(32);
    text.setString(getClassName(p1Class));
    text.setPosition(150.f, 240.f);
    window.draw(text);

    text.setCharacterSize(24);
    text.setString(
        getClassBonusText(p1Class)
    );
    text.setPosition(150.f, 300.f);
    window.draw(text);

    text.setString(
        "1 Warrior\n"
        "2 Berserker\n"
        "3 Thug\n"
        "4 Ranger"
    );
    text.setPosition(150.f, 450.f);
    window.draw(text);

    // PLAYER 2

    text.setCharacterSize(36);
    text.setString("PLAYER 2");
    text.setPosition(1100.f, 180.f);
    window.draw(text);

    text.setCharacterSize(32);
    text.setString(getClassName(p2Class));
    text.setPosition(1100.f, 240.f);
    window.draw(text);

    text.setCharacterSize(24);
    text.setString(
        getClassBonusText(p2Class)
    );
    text.setPosition(1100.f, 300.f);
    window.draw(text);

    text.setString(
        "Num1 Warrior\n"
        "Num2 Berserker\n"
        "Num3 Thug\n"
        "Num4 Ranger"
    );
    text.setPosition(1100.f, 450.f);
    window.draw(text);

    // START

    text.setCharacterSize(32);
    text.setString(
        "SPACE - START MATCH"
    );
    text.setPosition(
        700.f,
        850.f
    );
    window.draw(text);
}


std::string getClassBonusText(
    CharacterClass characterClass
)
{
    switch (characterClass)
    {
    case CharacterClass::Warrior:
        return
            "+20% HP\n"
            "+10% Resistance";

    case CharacterClass::Berserker:
        return
            "+25% Damage\n"
            "-20% HP";

    case CharacterClass::Thug:
        return
            "+10% Speed\n"
            "Dodge Chance";

    case CharacterClass::Ranger:
        return
            "+10% Speed\n"
            "+25% Ranged Damage";
    }

    return "";
}

void drawGameOverMenu(
    sf::RenderWindow& window,
    sf::Font& font,
    int winner
)
{
    sf::Text text;

    text.setFont(font);
    text.setFillColor(sf::Color::White);

    std::string winnerText;

    if (winner == 1)
    {
        winnerText = "PLAYER 1 WINS!";
    }
    else
    {
        winnerText = "PLAYER 2 WINS!";
    }

    text.setCharacterSize(64);
    text.setString("VICTORY");
    text.setPosition(
        700.f,
        150.f
    );

    window.draw(text);

    text.setCharacterSize(48);
    text.setString(winnerText);
    text.setPosition(
        600.f,
        350.f
    );

    window.draw(text);

    text.setCharacterSize(32);
    text.setString(
        "PRESS ENTER TO RETURN TO MAP SELECTION"
    );

    text.setPosition(
        350.f,
        600.f
    );

    window.draw(text);
}