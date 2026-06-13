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

    text.setFillColor(
        sf::Color::White
    );

    text.setOutlineThickness(2.f);

    text.setOutlineColor(
        sf::Color::Black
    );

    std::vector<sf::String> lines =
    {
        L"Wybór mapy",
        L"",
        L"1 - Zachód Słońca",
        L"2 - Zimowe Szczyty",
        L"3 - Zamek",
        L"",
        L"Wybrano: " + std::to_wstring(selectedMap),
        L"",
        L"Wciśnij ENTER, aby przejść do wyboru klas"
    };

    float y = 300.f;

    for (const auto& line : lines)
    {
        text.setString(line);

        sf::FloatRect bounds =
            text.getLocalBounds();

        text.setOrigin(
            bounds.left + bounds.width / 2.f,
            0.f
        );

        text.setPosition(
            window.getSize().x / 2.f,
            y
        );

        window.draw(text);

        y += 50.f;
    }


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
    text.setOutlineThickness(2.f);
    text.setOutlineColor(sf::Color::Black);

    text.setCharacterSize(48);
    text.setString(
        sf::String(L"Wybór klasy")
    );

    centerText(
        text,
        window.getSize().x / 2.f,
        70.f
    );

    window.draw(text);

    text.setCharacterSize(36);
    text.setString("Gracz 1");

    centerText(
        text,
        480.f,
        200.f
    );

    window.draw(text);

    text.setCharacterSize(32);
    text.setString(
        getClassName(p1Class)
    );

    centerText(
        text,
        480.f,
        260.f
    );

    window.draw(text);

    text.setCharacterSize(24);
    text.setOrigin(0.f, 0.f);

    text.setString(
        getClassBonusText(p1Class)
    );

    text.setPosition(
        350.f,
        300.f
    );

    window.draw(text);

    text.setString(
        sf::String(
            L"1 - Wojownik\n"
            L"2 - Berserker\n"
            L"3 - Zbir\n"
            L"4 - Łowca"
        )
    );

    text.setPosition(
        350.f,
        450.f
    );

    window.draw(text);

    text.setCharacterSize(36);
    text.setString("Gracz 2");

    centerText(
        text,
        1440.f,
        200.f
    );

    window.draw(text);

    text.setCharacterSize(32);
    text.setString(
        getClassName(p2Class)
    );

    centerText(
        text,
        1440.f,
        260.f
    );

    window.draw(text);

    text.setCharacterSize(24);
    text.setOrigin(0.f, 0.f);

    text.setString(
        getClassBonusText(p2Class)
    );

    text.setPosition(
        1300.f,
        300.f
    );

    window.draw(text);

    text.setString(
        sf::String(
            L"Num1 - Wojownik\n"
            L"Num2 - Berserker\n"
            L"Num3 - Zbir\n"
            L"Num4 - Łowca"
        )
    );

    text.setPosition(
        1300.f,
        450.f
    );

    window.draw(text);

    text.setCharacterSize(32);

    text.setString(
        sf::String(
            L"Wciśnij ENTER aby rozpocząć grę"
        )
    );

    centerText(
        text,
        window.getSize().x / 2.f,
        900.f
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
    text.setOutlineThickness(3.f);
    text.setOutlineColor(sf::Color::Black);

    text.setCharacterSize(80);
    text.setString(
        sf::String(L"KONIEC GRY")
    );

    centerText(
        text,
        window.getSize().x / 2.f,
        180.f
    );

    window.draw(text);

    text.setCharacterSize(56);

    if (winner == 1)
    {
        text.setString(
            sf::String(L"Gracz 1 wygrywa!")
        );
        text.setFillColor(
            sf::Color(100, 180, 255)
        );
    }
    else
    {
        text.setString(
            sf::String(L"Gracz 2 wygrywa!")
        );
        text.setFillColor(
            sf::Color(255, 120, 120)
        );
    }

    centerText(
        text,
        window.getSize().x / 2.f,
        380.f
    );

    window.draw(text);

    text.setCharacterSize(32);
    text.setFillColor(
        sf::Color::White
    );

    text.setString(
        sf::String(
            L"Naciśnij ENTER aby wrócić do wyboru map"
        )
    );

    centerText(
        text,
        window.getSize().x / 2.f,
        800.f
    );

    window.draw(text);
}
void centerText(
    sf::Text& text,
    float x,
    float y
)
{
    sf::FloatRect bounds =
        text.getLocalBounds();

    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    text.setPosition(
        x,
        y
    );
}