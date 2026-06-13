#include "Game.h"
#include "GameState.h"
#include <algorithm>
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

    fPressedLastFrame = false;
    rCtrlPressedLastFrame = false;

    map = nullptr;

    if (!font.loadFromFile("assets/fonts/Tiny5-Regular.ttf"))
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

    bool fJustPressed =
        sf::Keyboard::isKeyPressed(sf::Keyboard::F)
        &&
        !fPressedLastFrame;

    fPressedLastFrame =
        sf::Keyboard::isKeyPressed(sf::Keyboard::F);

    bool rCtrlJustPressed =
        sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)
        &&
        !rCtrlPressedLastFrame;

    rCtrlPressedLastFrame =
        sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);


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
            map = new Map(
                sf::Vector2u(
                    1920,
                    1080
                ),
                selectedMap
            );

            sf::Vector2f player1Spawn =
                map->getPlayerSpawn(0);

            sf::Vector2f player2Spawn =
                map->getPlayerSpawn(1);

            player1 = new Player(
                player1Spawn.x,
                player1Spawn.y,

                p1Class,

                sf::Keyboard::A,
                sf::Keyboard::D,
                sf::Keyboard::W,
                sf::Keyboard::S
            );

            player2 = new Player(
                player2Spawn.x,
                player2Spawn.y,

                p2Class,

                sf::Keyboard::Left,
                sf::Keyboard::Right,
                sf::Keyboard::Up,
                sf::Keyboard::Down
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

    if (fJustPressed)
    {
        if (
            player1->getCurrentWeapon()
            &&
            player1->getCurrentWeapon()->getName() == "Pistol"
            )
        {
            if (player1->canAttack())
            {
                pociski.push_back(
                    Pocisk(
                        player1->isFacingRight()
                        ? player1->getPosition().x + 150.f
                        : player1->getPosition().x - 150.f,

                        player1->getPosition().y + 40.f,

                        player1->isFacingRight()
                    )
                );

                player1->startAttackCooldown();
            }
        }
        else
        {
            player1->attack(*player2);
        }
    }

    if (rCtrlJustPressed)
    {
        if (
            player2->getCurrentWeapon()
            &&
            player2->getCurrentWeapon()->getName()
            == "Pistol"
            )
        {
            if (player2->canAttack())
            {
                pociski.push_back(
                    Pocisk(
                        player2->isFacingRight()
                        ? player2->getPosition().x + 150.f
                        : player2->getPosition().x - 150.f,

                        player2->getPosition().y + 40.f,

                        player2->isFacingRight()
                    )
                );

                player2->startAttackCooldown();
            }
        }
        else
        {
            player2->attack(
                *player1
            );
        }
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

        droppedWeapon->setDropped(
            true
        );

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

        droppedWeapon->setDropped(
            true
        );

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

    map->updateWeaponSpawner();

    player1->update(
        map->getPlatforms()
    );

    player2->update(
        map->getPlatforms()
    );

    if (player1->shouldDropWeapon())
    {

        std::unique_ptr<Weapon> droppedWeapon =
            player1->takeCurrentWeapon();


        droppedWeapon->setDropped(
            true
        );

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

    if (player2->shouldDropWeapon())
    {

        std::unique_ptr<Weapon> droppedWeapon =
            player2->takeCurrentWeapon();

        droppedWeapon->setDropped(
            true
        );

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

    for (
        auto it = pociski.begin();
        it != pociski.end();
        )
    {
        bool removeBullet = false;

        it->update();

        if (
            it->getX() < -500.f
            ||
            it->getX() > map->getWorldWidth() + 500.f
            )
        {
            removeBullet = true;
        }


        if (
            it->getBounds().intersects(
                player1->getBounds()
            )
            )
        {
            player1->takeDamage(
                2.f
            );

            if (
                it->getBounds().left
                <
                player1->getBounds().left
                )
            {
                player1->addKnockback(
                    8.f,
                    -5.f
                );
            }
            else
            {
                player1->addKnockback(
                    -12.f,
                    -5.f
                );
            }

            removeBullet = true;
        }

        if (
            it->getBounds().intersects(
                player2->getBounds()
            )
            )
        {
            player2->takeDamage(
                2.f
            );

            if (
                it->getBounds().left
                <
                player2->getBounds().left
                )
            {
                player2->addKnockback(
                    12.f,
                    -5.f
                );
            }
            else
            {
                player2->addKnockback(
                    -8.f,
                    -5.f
                );
            }

            removeBullet = true;
        }

        if (removeBullet)
        {
            it = pociski.erase(it);
        }
        else
        {
            ++it;
        }
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

            droppedWeapon->setDropped(
                true
            );

            droppedWeapon->setPosition(
                player1->getPosition().x,
                player1->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        sf::Vector2f player1Spawn =
            map->getPlayerSpawn(0);

        player1->respawn(
            player1Spawn.x,
            player1Spawn.y
        );
    }

    if (player2->getHp() <= 0)
    {
        player2->addDeath();

        if (player2->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player2->takeCurrentWeapon();

            droppedWeapon->setDropped(
                true
            );

            droppedWeapon->setPosition(
                player2->getPosition().x,
                player2->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        sf::Vector2f player2Spawn =
            map->getPlayerSpawn(1);

        player2->respawn(
            player2Spawn.x,
            player2Spawn.y
        );
    }

    if (
        player1->getPosition().y
    > map->getDeathZoneY()
        )
    {
        player1->addDeath();

        if (player1->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player1->takeCurrentWeapon();

            droppedWeapon->setDropped(
                true
            );

            droppedWeapon->setPosition(
                player1->getPosition().x,
                player1->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        sf::Vector2f player1Spawn =
            map->getPlayerSpawn(0);

        player1->respawn(
            player1Spawn.x,
            player1Spawn.y
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
    > map->getDeathZoneY()
        )
    {
        player2->addDeath();


        if (player2->getHasWeapon())
        {
            std::unique_ptr<Weapon> droppedWeapon =
                player2->takeCurrentWeapon();

            droppedWeapon->setDropped(
                true
            );

            droppedWeapon->setPosition(
                player2->getPosition().x,
                player2->getPosition().y
            );

            map->addWeapon(
                std::move(droppedWeapon)
            );
        }

        sf::Vector2f player2Spawn =
            map->getPlayerSpawn(1);

        player2->respawn(
            player2Spawn.x,
            player2Spawn.y
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
    const float MIN_ZOOM = 1.2f;
    float targetZoom = MIN_ZOOM;

    if (distance > 600.f)
    {
        targetZoom +=
            (distance - 600.f)
            / 2500.f;
    }

    targetZoom =
        std::clamp(
            targetZoom,
            1.f,
            3.f
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

    float middleY =
        (
            player1->getPosition().y
            +
            player2->getPosition().y
            ) / 2.f;

    float halfCameraWidth =
        camera.getSize().x / 2.f;

    float halfCameraHeight =
        camera.getSize().y / 2.f;

    float cameraX =
        middleX;

    if (map->getWorldWidth() > camera.getSize().x)
    {
        cameraX =
            std::clamp(
                middleX,
                halfCameraWidth - 300.f,
                map->getWorldWidth()
                - halfCameraWidth
                + 500.f
            );
    }
    else
    {
        cameraX = map->getWorldWidth() / 2.f;
    }

    float cameraY =
        middleY;

    if (map->getDeathZoneY() > camera.getSize().y)
    {
        cameraY =
            std::clamp(
                middleY,
                halfCameraHeight,
                map->getDeathZoneY() - halfCameraHeight
            );
    }
    else
    {
        cameraY = map->getDeathZoneY() / 2.f;
    }

    const float CAMERA_SMOOTHNESS = 0.1f;

    sf::Vector2f currentCenter =
        camera.getCenter();

    currentCenter.x +=
        (cameraX - currentCenter.x)
        * 0.08f;


    currentCenter.y +=
        (cameraY - currentCenter.y)
        * 0.08f;

    camera.setCenter(
        currentCenter
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
