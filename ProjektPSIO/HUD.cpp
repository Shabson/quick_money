#include "HUD.h"

void drawHUD(
    sf::RenderWindow& window,
    sf::Font& font,
    Player* player1,
    Player* player2
)
{
    // PLAYER 1 HP

    sf::RectangleShape hpBack1;

    hpBack1.setSize(
        sf::Vector2f(
            400.f,
            30.f
        )
    );

    hpBack1.setFillColor(
        sf::Color(60, 60, 60)
    );

    hpBack1.setPosition(
        30.f,
        20.f
    );

    window.draw(hpBack1);
    float hpPercent1 =
        static_cast<float>(player1->getHp())/static_cast<float>(player1->getMaxHp());

    sf::RectangleShape hpFront1;

    hpFront1.setSize(
        sf::Vector2f(
            400.f * hpPercent1,
            30.f
        )
    );

    hpFront1.setFillColor(
        sf::Color::Red
    );

    hpFront1.setPosition(
        30.f,
        20.f
    );

    hpFront1.setOutlineColor(sf::Color::Black);
    hpFront1.setOutlineThickness(2.f);

    window.draw(hpFront1);


    // PLAYER 2 HP

    sf::RectangleShape hpBack2;

    hpBack2.setSize(
        sf::Vector2f(
            400.f,
            30.f
        )
    );

    hpBack2.setFillColor(
        sf::Color(60, 60, 60)   
    );

    hpBack2.setPosition(
        1490.f,
        20.f
    );
    
	hpBack2.setOutlineColor(sf::Color::Black);
    hpBack2.setOutlineThickness(2.f);

    window.draw(hpBack2);

    float hpPercent2 =
        static_cast<float>(player2->getHp())/static_cast<float>(player2->getMaxHp());

    sf::RectangleShape hpFront2;

    hpFront2.setSize(
        sf::Vector2f(
            400.f * hpPercent2,
            30.f
        )
    );

    hpFront2.setFillColor(
        sf::Color::Red
    );

    hpFront2.setPosition(
        1490.f,
        20.f
    );

    window.draw(hpFront2);


    // TEKST

    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(
        sf::Color::White
    );
    text.setOutlineThickness(2.f);
    text.setOutlineColor(sf::Color::Black);

    text.setString(
        "P1"
    );

    text.setPosition(
        30.f,
        60.f
    );

    window.draw(text);

    text.setString(
        sf::String(
            L"Śmierci: "
        )
        +
        std::to_string(
            player1->getDeaths()
        )
        +
        "/5"
    );

    text.setPosition(
        30.f,
        100.f
    );

    window.draw(text);

    text.setString(
        "P2"
    );

    text.setPosition(
        1840.f,
        60.f
    );

    window.draw(text);

    text.setString(
        sf::String(
            L"Śmierci: "
        )
        +
        std::to_string(
            player2->getDeaths()
        )
        +
        "/5"
    );

    text.setPosition(
        1710.f,
        100.f
    );

    window.draw(text);
}