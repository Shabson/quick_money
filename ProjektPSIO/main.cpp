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

    Player player1(300.f, 500.f);

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

        // UPDATE
        player1.update(map.getPlatforms());

        map.update(player1.getPosition().x);

        // DRAW
        window.clear();

        map.draw(window);

        player1.draw(window);

        window.display();
    }

    return 0;
}