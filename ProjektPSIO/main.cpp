#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(1920, 1080),
        "Knur Fight"
    );

    window.setFramerateLimit(60);

    Game game(window);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (
                event.type
                ==
                sf::Event::Closed
                )
            {
                window.close();
            }
        }

        game.run();
    }

    return 0;
}
