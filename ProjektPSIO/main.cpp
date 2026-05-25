#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Weapon.h"
using namespace std;
int main()
{

    sf::Vector2u windowSize(1920, 1080);

    sf::RenderWindow window(
        sf::VideoMode(windowSize.x, windowSize.y),
        "Knur Fight"
    );

    window.setFramerateLimit(60);

    float currentZoom = 1.f;

    sf::View camera;

    camera.setCenter(windowSize.x / 2.f, windowSize.y / 2.f);



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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            player1.attack(player2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            player2.attack(player1);
        }


        // UPDATE
        player1.update(map.getPlatforms());

        player2.update(map.getPlatforms());

        cout
            << "P1 HP: "
            << player1.getHp()

            << " | P2 HP: "

            << player2.getHp()
            << std::endl;


        player1.resolveCollision(player2);


        if (player1.getHp() <= 0)
        {
            player1.respawn(300.f, 500.f);
        }

        if (player2.getHp() <= 0)
        {
            player2.respawn(700.f, 500.f);
        }

        if (player1.getPosition().y > 1400.f)
        {
            player1.respawn(300.f, 500.f);
        }

        if (player2.getPosition().y > 1400.f)
        {
            player2.respawn(700.f, 500.f);
        }


        for (auto it = map.getWeapons().begin();
            it != map.getWeapons().end();)
        {
            if (
                player1.getBounds().intersects(
                    it->getBounds())
                )
            {
                player1.setHasWeapon(true);

                it =
                    map.getWeapons().erase(it);
            }
            else
            {
                ++it;
            }
        }



        float middleX =
            (player1.getPosition().x +
                player2.getPosition().x) / 2.f;

        float distance =
            abs(
                player1.getPosition().x
                - player2.getPosition().x
            );
        float targetZoom =
            1.f + distance / 2000.f;

        targetZoom = std::clamp(
            targetZoom,
            1.f,
            1.8f
        );
        currentZoom +=
            (targetZoom - currentZoom)
            * 0.05f;

        camera.setSize(
            windowSize.x * currentZoom,
            windowSize.y * currentZoom
        );


        camera.setCenter(
            middleX,
            windowSize.y / 2.f
        );

        // DRAW
        window.clear();

        window.setView(camera);

        map.draw(window, camera);

        player1.draw(window);

        player2.draw(window);

        window.display();
    }

    return 0;
}