#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <memory>
#include <utility>
#include "HUD.h"

Game::Game(
    sf::RenderWindow& window
)
    : window(window)
{
    currentZoom = 1.f;

    camera.setCenter(
        1920 / 2.f,
        1080 / 2.f
    );

    gameState =
        GameState::MapSelection;

    p1Class =
        CharacterClass::Warrior;

    p2Class =
        CharacterClass::Warrior;

    selectedMap = 1;
    winner = 0;
    player1 = nullptr;
    player2 = nullptr;
    
    enterPressedLastFrame = false;

    map = nullptr;

    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cout
            << "FONT LOAD FAILED"
            << std::endl;
    }
}   


void Game::run()
{
    bool enterJustPressed =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
        &&
        !enterPressedLastFrame;

    enterPressedLastFrame =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

    if (gameState ==
        GameState::ClassSelection)
    {
        handleClassSelection(
            p1Class,
            p2Class,
            gameState,
            enterJustPressed
        );

        if (
            gameState ==
            GameState::Playing
            )
        {
            player1 = new Player(
                300.f,
                500.f,

                p1Class,

                sf::Keyboard::A,
                sf::Keyboard::D,
                sf::Keyboard::W,
                sf::Keyboard::S
            );

            player2 = new Player(
                700.f,
                500.f,

                p2Class,

                sf::Keyboard::Left,
                sf::Keyboard::Right,
                sf::Keyboard::Up,
                sf::Keyboard::Down
            );

            map = new Map(
                sf::Vector2u(
                    1920,
                    1080
                ),
                selectedMap
            );

            pociski.clear();
        }

        window.clear(sf::Color::Black);

        window.setView(
            window.getDefaultView()
        );

        drawClassSelectionMenu(
            window,
            font,
            p1Class,
            p2Class
           );

        window.display();

        return;
    }

    if (gameState ==
        GameState::MapSelection)
    {
        handleMapSelection(
            selectedMap,
            gameState,
            enterJustPressed
        );

        window.clear(
            sf::Color(20, 30, 60)
        );

        window.setView(
            window.getDefaultView()
        );
        drawMapSelectionMenu(
            window,
            font,
            selectedMap
        );

        window.display();

        return;
    }  

    if (gameState == GameState::GameOver)
    {
        if (enterJustPressed)
        {
            delete player1;
            delete player2;
            delete map;

            player1 = nullptr;
            player2 = nullptr;
            map = nullptr;

            pociski.clear();

            winner = 0;

			resetCamera();

            gameState =
                GameState::MapSelection;
        }

        window.clear(
            sf::Color::Black
        );

        window.setView(
            window.getDefaultView()
        );

        drawGameOverMenu(
            window,
            font,
            winner
        );

        window.display();

        return;
    }

    player1->handleInput();

    player2->handleInput();

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::F
        )
        )
    {
        player1->attack(
            *player2
        );
    }

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::RControl
        )
        )
    {
        player2->attack(
            *player1
        );
    }

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Q
        )
        &&
        player1->getHasWeapon()
        )
    {
        std::unique_ptr<Weapon> droppedWeapon =
            player1->takeCurrentWeapon();

        if (player1->isFacingRight())
        {
            droppedWeapon->setPosition(
                player1->getPosition().x + 150.f,
                player1->getPosition().y
            );
        }
        else
        {
            droppedWeapon->setPosition(
                player1->getPosition().x - 150.f,
                player1->getPosition().y
            );
        }

        map->addWeapon(
            std::move(droppedWeapon)
        );
    }

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::RShift
        )
        &&
        player2->getHasWeapon()
        )
    {
        std::unique_ptr<Weapon> droppedWeapon =
            player2->takeCurrentWeapon();

        if (player2->isFacingRight())
        {
            droppedWeapon->setPosition(
                player2->getPosition().x + 150.f,
                player2->getPosition().y
            );
        }
        else
        {
            droppedWeapon->setPosition(
                player2->getPosition().x - 150.f,
                player2->getPosition().y
            );
        }
  

        map->addWeapon(
            std::move(droppedWeapon)
        );
    }


    // UPDATE

    player1->update(
        map->getPlatforms()
    );

    player2->update(
        map->getPlatforms()
    );

    for (auto& pocisk : pociski)
    {
        pocisk.update();
    }

    player1->resolveCollision(
        *player2
    );



    // RESPAWN

    if (player1->getHp() <= 0)
    {
        player1->addDeath();

        if (player1->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player1->takeCurrentWeapon();

            droppedWeapon->setPosition(
                player1->getPosition().x,
                player1->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        player1->respawn(
            300.f,
            500.f
        );
    }

    if (player2->getHp() <= 0)
    {
        player2->addDeath();

        if (player2->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player2->takeCurrentWeapon();

            droppedWeapon->setPosition(
                player2->getPosition().x,
                player2->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        player2->respawn(
            700.f,
            500.f
        );
    }

    if (
        player1->getPosition().y
    > 1400.f
        )
    {
        player1->addDeath();

        if (player1->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player1->takeCurrentWeapon();

            droppedWeapon->setPosition(
                player1->getPosition().x,
                player1->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        player1->respawn(
            300.f,
            500.f
        );
    }

    if (player1->getDeaths() >= 5)
    {
        winner = 2;
        gameState = GameState::GameOver;
    }

    if (player2->getDeaths() >= 5)
    {
        winner = 1;
        gameState = GameState::GameOver;
    }

    if (
        player2->getPosition().y
    > 1400.f
        )
    {
        player2->addDeath();


        if (player2->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player2->takeCurrentWeapon();

            droppedWeapon->setPosition(
                player2->getPosition().x,
                player2->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        player2->respawn(
            300.f,
            500.f
        );
    }

    // WEAPON PICKUP

    for (
        auto it =
        map->getWeapons().begin();

        it != map->getWeapons().end();
        )
    {
        if (
            player1->getBounds()
            .intersects(
                (*it)->getBounds()
            )
            &&
            !player1->getHasWeapon()
            )
        {
            player1->setCurrentWeapon(
                std::move(*it)
            );

            it =
                map->getWeapons()
                .erase(it);
        }
        else if (
            player2->getBounds()
            .intersects(
                (*it)->getBounds()
            )
            &&
            !player2->getHasWeapon()
            )
        {
            player2->setCurrentWeapon(
                std::move(*it)
            );

            it =
                map->getWeapons()
                .erase(it);
        }
        else
        {
            ++it;
        }
    }

    // CAMERA

    float middleX =
        (
            player1->getPosition().x
            +
            player2->getPosition().x
            ) / 2.f;

    float distance =
        abs(
            player1->getPosition().x
            -
            player2->getPosition().x
        );

    float targetZoom =
        1.f + distance / 2000.f;

    targetZoom =
        std::clamp(
            targetZoom,
            1.f,
            1.8f
        );

    currentZoom +=
        (
            targetZoom
            - currentZoom
            ) * 0.05f;

    camera.setSize(
        1920 * currentZoom,
        1080 * currentZoom
    );

    camera.setCenter(
        middleX,
        1080 / 2.f
    );

    // DRAW

    window.clear();

    window.setView(camera);

    map->draw(
        window,
        camera
    );

    for (auto& pocisk : pociski)
    {
        pocisk.draw(window);
    }

    player1->draw(window);

    player2->draw(window);

    player1->drawCooldownBar(
        window
    );

    player2->drawCooldownBar(
        window
    );

    window.setView(
        window.getDefaultView()
    );

    drawHUD(
        window,
        font,
        player1,
        player2
    );
   

    window.display();
}

void Game::resetCamera()
{
    currentZoom = 1.f;

    camera.setSize(
        1920.f,
        1080.f
    );

    camera.setCenter(
        960.f,
        540.f
    );
}
