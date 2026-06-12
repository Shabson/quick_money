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
            L"Wybór mapy\n\n"
            L"1 - Zachód Słońca\n"
            L"2 - Zimowe Szczyty\n"
            L"3 - Zamek\n\n"
            L"Wybrano: "
        +
        std::to_wstring(selectedMap)
        +
        L"\n\nWciśnij ENTER"
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
        return "Wojownik";

    case CharacterClass::Berserker:
        return "Berserker";

    case CharacterClass::Thug:
        return "Zbir";

    case CharacterClass::Ranger:
        return "Łowca";
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
    text.setString(sf::String(L"Wybór klasy"));
    text.setPosition(650.f, 50.f);
    window.draw(text);

    text.setCharacterSize(36);
    text.setString("Gracz 1");
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
            L"1 - Wojownik\n"
            L"2 - Berserker\n"
            L"3 - Zbir\n"
            L"4 - Łowca"
    );
    text.setPosition(150.f, 450.f);
    window.draw(text);

    text.setCharacterSize(36);
    text.setString("Gracz 2");
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
        sf::String(
            L"Num1 - Wojownik\n"
            L"Num2 - Berserker\n"
            L"Num3 - Zbir\n"
            L"Num4 - Łowca"
        )
    );
    text.setPosition(1100.f, 450.f);
    window.draw(text);

    text.setCharacterSize(32);
    text.setString(
        L"Wciśnij ENTER aby rozpocząć grę"
    );
    text.setPosition(
        700.f,
        850.f
    );
    window.draw(text);
}


sf::String getClassBonusText(
    CharacterClass characterClass
)
{
    switch (characterClass)
    {
    case CharacterClass::Warrior:
        return
            L"+20% HP\n"
            L"+10% Odporności na obrażenia";

    case CharacterClass::Berserker:
        return
            L"+25% Zadawanych obrażeń\n"
            L"-20% HP";

    case CharacterClass::Thug:
        return
            L"+10% Prędkości poruszania się\n"
            L"+25% Szansy na unik";

    case CharacterClass::Ranger:
        return
            L"+10% Prędkości poruszania się\n"
            L"+25% Obrażeń dystansowych";
    }

    return L"";
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
        winnerText = "Gracz 1 wygrywa!";
    }
    else
    {
        winnerText = "Gracz 2 wygrywa!";
    }

    text.setCharacterSize(64);
    text.setString("Koniec Gry");
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
        L"Naciśnij ENTER aby powrócić do wyboru map"
    );

    text.setPosition(
        350.f,
        600.f
    );

    window.draw(text);
}