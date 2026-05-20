#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
int main()
{
    Map map;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Knur Fight");
    window.setFramerateLimit(60);

    Player player1(300.f, 500.f);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player1.handleInput();
        player1.update();
        map.draw(window);
        window.clear();
        player1.draw(window);
        window.display();
    }

    return 0;
}