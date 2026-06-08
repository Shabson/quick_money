#include "Game.h"
#include "GameState.h"
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
        GameState::ClassSelection;

    p1Class =
        CharacterClass::Warrior;

    p2Class =
        CharacterClass::Warrior;

    selectedMap = 1;

    player1 = nullptr;
    player2 = nullptr;

    map = nullptr;
}

void Game::run()
{
    if (gameState ==
        GameState::ClassSelection)
    {
        handleClassSelection(
            p1Class,
            p2Class,
            gameState
        );

        window.clear(
            sf::Color::Black
        );

        window.display();

        return;
    }

    if (gameState ==
        GameState::MapSelection)
    {
        handleMapSelection(
            selectedMap,
            gameState
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
        }

        window.clear(
            sf::Color::Blue
        );

        window.display();

        return;
    }

    // INPUT

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
        Weapon droppedWeapon =
            player1->getCurrentWeapon();

        if (player1->isFacingRight())
        {
            droppedWeapon.setPosition(
                player1->getPosition().x + 150.f,
                player1->getPosition().y
            );
        }
        else
        {
            droppedWeapon.setPosition(
                player1->getPosition().x - 150.f,
                player1->getPosition().y
            );
        }

        map->addWeapon(
            droppedWeapon
        );

        player1->dropWeapon();
    }

    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::RShift
        )
        &&
        player2->getHasWeapon()
        )
    {
        Weapon droppedWeapon =
            player2->getCurrentWeapon();

        if (player2->isFacingRight())
        {
            droppedWeapon.setPosition(
                player2->getPosition().x + 150.f,
                player2->getPosition().y
            );
        }
        else
        {
            droppedWeapon.setPosition(
                player2->getPosition().x - 150.f,
                player2->getPosition().y
            );
        }
  

        map->addWeapon(
            droppedWeapon
        );

        player2->dropWeapon();
    }


    // UPDATE

    player1->update(
        map->getPlatforms()
    );

    player2->update(
        map->getPlatforms()
    );

    player1->resolveCollision(
        *player2
    );

    // RESPAWN

    if (player1->getHp() <= 0)
    {
        player1->addDeath();

        player1->respawn(
            300.f,
            500.f
        );
    }

    if (player2->getHp() <= 0)
    {
        player2->addDeath();

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

        player1->respawn(
            300.f,
            500.f
        );
    }

    if (
        player2->getPosition().y
    > 1400.f
        )
    {
        player2->addDeath();

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
                it->getBounds()
            )
            &&
            !player1->getHasWeapon()
            )
        {
            player1->setCurrentWeapon(
                *it
            );

            it =
                map->getWeapons()
                .erase(it);
        }
        else if (
            player2->getBounds()
            .intersects(
                it->getBounds()
            )
            &&
            !player2->getHasWeapon()
            )
        {
            player2->setCurrentWeapon(
                *it
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

    player1->draw(window);

    player2->draw(window);

    player1->drawCooldownBar(
        window
    );

    player2->drawCooldownBar(
        window
    );

    window.display();
}