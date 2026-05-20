#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"
int main()
{

    sf::Vector2u windowSize(1920, 1080);

    sf::RenderWindow window(
        sf::VideoMode(windowSize.x, windowSize.y),
        "Knur Fight"
    );

    window.setFramerateLimit(60);


    Player player1(
        300.f,
        500.f,

        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::W,
        sf::Keyboard::S
    );

    Player player2(
        700.f,
        500.f,

        sf::Keyboard::Left,
        sf::Keyboard::Right,
        sf::Keyboard::Up,
        sf::Keyboard::Down
    );

    Map map(windowSize);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // INPUT
        player1.handleInput();

        player2.handleInput();


        // UPDATE
        player1.update(map.getPlatforms());

        player2.update(map.getPlatforms());

        player1.resolveCollision(player2);



        float middleX =
            (
                player1.getPosition().x +
                player2.getPosition().x
                ) / 2.f;

        map.update(middleX);

        // DRAW
        window.clear();

        map.draw(window);

        player1.draw(window);

        player2.draw(window);

        window.display();
    }

    return 0;
}