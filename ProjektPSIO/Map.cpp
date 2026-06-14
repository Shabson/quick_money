#include "Map.h"
#include "Weapon.h"
#include <algorithm>
#include <cmath>
#include <utility>

Map::Map(sf::Vector2u windowSize, int mapType)
{   
    this->windowSize = windowSize;
    deathZoneY = 1400.f;
    worldWidth = 1920.f;
    randomGenerator.seed(
        std::random_device{}()
    );

   lastSpawnIndex = -1;

    switch (mapType)
    {
    case 1:
        loadMap1();
        break;
    case 2:
        loadMap2();
        break;
	case 3:
		loadMap3();
		break;
    default:
        loadMap1();
        break;
    }
}

void Map::loadMap1()
{
    backgroundLayers.clear();
    platforms.clear();
    playerSpawns.clear();
    weaponSpawns.clear();
    weapons.clear();
    loadPlatformTexture(
        "assets/textures/sandbrick_grass_alt_tileset_2.png"
    );

    deathZoneY = 1400.f;
    worldWidth = 1920.f;

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-bg.png",
            0.05f,
            windowSize,
            false
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-montain-far.png",
            0.2f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-mountains.png",
            0.3f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-trees.png",
            0.5f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/parallax-mountain-foreground-trees.png",
            0.6f,
            windowSize
        )
    );

    platforms.push_back(
        Platform(0.f, 1100.f, 40.f, platformTexture)
    );

    platforms.push_back(
        Platform(200.f, 850.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(500.f, 650.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(200.f, 450.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(500.f, 250.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(800.f, 550.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(800.f, 850.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(1350.f, 850.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(1650.f, 650.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(1350.f, 450.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(1650.f, 250.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(950.f, 250.f, 4.f, platformTexture)
    );

    platforms.push_back(
        Platform(750.f, 250.f, 3.f, platformTexture)
    );

    platforms.push_back(
        Platform(1150.f, 250.f, 3.f, platformTexture)
    );

    platforms.push_back(
        Platform(750.f, 850.f, 3.f, platformTexture)
    );

    platforms.push_back(
        Platform(1150.f, 850.f, 3.f, platformTexture)
    );

    playerSpawns.push_back(
        sf::Vector2f(250.f, 760.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(550.f, 360.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(1400.f, 760.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(1700.f, 360.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(650.f, 600.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(960.f, 500.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(1260.f, 600.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(960.f, 200.f)
    );
}

void Map::loadMap2()
{
    backgroundLayers.clear();
    platforms.clear();
    playerSpawns.clear();
    weaponSpawns.clear();
    weapons.clear();
    loadPlatformTexture(
        "assets/textures/rock_ice_alt_tileset_0.png"
    );
    deathZoneY = 1900.f;
    worldWidth = 3500.f;

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/sky_lightened.png",
            0.05f,
            windowSize,
            false
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/glacial_mountains_lightened.png",
            0.2f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/clouds_bg.png",
            0.3f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/clouds_mg_1_lightened.png",
            0.5f,
            windowSize
        )
    );

 
    platforms.push_back(
        Platform(0.f, 1500.f, 73.f, platformTexture)
    );

    platforms.push_back(
        Platform(240.f, 1250.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(620.f, 1050.f, 7.f, platformTexture)
    );

    platforms.push_back(
        Platform(1080.f, 850.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(1450.f, 1150.f, 12.f, platformTexture)
    );

    platforms.push_back(
        Platform(1650.f, 850.f, 5.f, platformTexture)
    );

    platforms.push_back(
        Platform(1450.f, 650.f, 5.f, platformTexture)
    );

    platforms.push_back(
        Platform(1850.f, 650.f, 5.f, platformTexture)
    );

    platforms.push_back(
        Platform(2450.f, 850.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(2850.f, 1050.f, 7.f, platformTexture)
    );

    platforms.push_back(
        Platform(3150.f, 1250.f, 6.f, platformTexture)
    );

    platforms.push_back(
        Platform(1600.f, 400.f, 8.f, platformTexture)
    );

    playerSpawns.push_back(sf::Vector2f(300.f, 1160.f));
    playerSpawns.push_back(sf::Vector2f(3200.f, 1160.f));

    weaponSpawns.push_back(sf::Vector2f(350.f, 1200.f));
    weaponSpawns.push_back(sf::Vector2f(775.f, 1000.f));
    weaponSpawns.push_back(sf::Vector2f(1200.f, 800.f));
    weaponSpawns.push_back(sf::Vector2f(1750.f, 800.f));
    weaponSpawns.push_back(sf::Vector2f(1550.f, 600.f));
    weaponSpawns.push_back(sf::Vector2f(1950.f, 600.f));
    weaponSpawns.push_back(sf::Vector2f(1750.f, 350.f));
    weaponSpawns.push_back(sf::Vector2f(2600.f, 800.f));
    weaponSpawns.push_back(sf::Vector2f(3025.f, 1000.f));
}

void Map::loadMap3()
{
    backgroundLayers.clear();
    platforms.clear();
    playerSpawns.clear();
    weaponSpawns.clear();
    weapons.clear();
    loadPlatformTexture(
        "assets/textures/wood_moss_alt_tileset_3.png"
    );

    deathZoneY = 2200.f;
    worldWidth = 4200.f;

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/Plan 4.png",
            0.05f,
            windowSize,
            false
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/Plan 3.png",
            0.6f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/Plan 2.png",
            0.3f,
            windowSize
        )
    );

    backgroundLayers.push_back(
        std::make_unique<ParallaxLayer>(
            "assets/textures/Plan 1.png",
            0.5f,
            windowSize
        )
    );


    platforms.push_back(
        Platform(0.f, 1700.f, 88.f, platformTexture)
    );

    platforms.push_back(
        Platform(300.f, 1450.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(700.f, 1200.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(1100.f, 950.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(1750.f, 1350.f, 12.f, platformTexture)
    );

    platforms.push_back(
        Platform(1900.f, 1000.f, 10.f, platformTexture)
    );

    platforms.push_back(
        Platform(2050.f, 650.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(3000.f, 950.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(3400.f, 1200.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(3800.f, 1450.f, 8.f, platformTexture)
    );

    platforms.push_back(
        Platform(450.f, 700.f, 5.f, platformTexture)
    );

    platforms.push_back(
        Platform(3500.f, 700.f, 5.f, platformTexture)
    );

    platforms.push_back(
        Platform(1950.f, 350.f, 10.f, platformTexture)
    );

    playerSpawns.push_back(
        sf::Vector2f(350.f, 1350.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(3850.f, 1350.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(1200.f, 850.f)
    );

    playerSpawns.push_back(
        sf::Vector2f(3000.f, 850.f)
    );
    weaponSpawns.push_back(
        sf::Vector2f(500.f, 1400.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(900.f, 1150.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(1300.f, 900.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(2000.f, 1300.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(2150.f, 950.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(2250.f, 600.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(3100.f, 900.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(3500.f, 1150.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(3900.f, 1400.f)
    );

    weaponSpawns.push_back(
        sf::Vector2f(2200.f, 300.f)
    );
}

void Map::draw(
    sf::RenderWindow& window,
    const sf::View& camera
)
{
    for (auto& layer : backgroundLayers)
    {
        layer->draw(window, camera);
    }

    window.setView(camera);

    for (auto& platform : platforms)
    {
        platform.draw(window);
    }

    for (auto& weapon : weapons)
    {
        weapon->draw(window);
    }

}

std::vector<Platform>& Map::getPlatforms()
{
    return platforms;
}

std::vector<std::unique_ptr<Weapon>>& Map::getWeapons()
{
    return weapons;
}

void Map::addWeapon(std::unique_ptr<Weapon> weapon)
{
    weapons.push_back(std::move(weapon));
}

void Map::updateWeaponSpawner()
{
    for (
        auto it = weapons.begin();
        it != weapons.end();
        )
    {
        (*it)->update();

        if ((*it)->shouldDespawn())
        {
            it = weapons.erase(it);
        }
        else
        {
            ++it;
        }
    }
        
    if (weaponSpawnClock.getElapsedTime().asSeconds() < 5.f)
    {
        return;
    }

    weaponSpawnClock.restart();
    spawnRandomWeapon();
}

void Map::spawnRandomWeapon()
{
    if (
        weaponSpawns.empty()
        ||
        weapons.size() >= weaponSpawns.size()
        )
    {
        return;
    }

    std::vector<sf::Vector2f> availableSpawns;

    for (const auto& spawn : weaponSpawns)
    {
        bool occupied = false;

        for (const auto& weapon : weapons)
        {
            sf::Vector2f weaponPosition =
                weapon->getPosition();

            if (
                std::abs(weaponPosition.x - spawn.x) < 5.f
                &&
                std::abs(weaponPosition.y - spawn.y) < 5.f
                )
            {
                occupied = true;
                break;
            }
        }

        if (!occupied)
        {
            availableSpawns.push_back(spawn);
        }
    }

    if (availableSpawns.empty())
    {
        return;
    }

    std::uniform_int_distribution<std::size_t> spawnDistribution(
        0,
        availableSpawns.size() - 1
    );

    std::uniform_int_distribution<int> weaponDistribution(0, 4);

    sf::Vector2f spawn =
        availableSpawns[spawnDistribution(randomGenerator)];

    switch (weaponDistribution(randomGenerator))
    {
    case 0:
        weapons.push_back(std::make_unique<Sword>(spawn.x, spawn.y));
        break;
    case 1:
        weapons.push_back(std::make_unique<Katana>(spawn.x, spawn.y));
        break;
    case 2:
        weapons.push_back(std::make_unique<Club>(spawn.x, spawn.y));
        break;
    case 3:
        weapons.push_back(std::make_unique<Spear>(spawn.x, spawn.y));
        break;
    default:
        weapons.push_back(std::make_unique<Pistol>(spawn.x, spawn.y));
        break;
    }
}

sf::Vector2f Map::getPlayerSpawn(int playerIndex)
{
    if (playerSpawns.empty())
    {
        return sf::Vector2f(300.f, 500.f);
    }

    std::uniform_int_distribution<int> dist(
        0,
        static_cast<int>(playerSpawns.size()) - 1
    );

    int spawnIndex;

    do
    {
        spawnIndex =
            dist(randomGenerator);
    } while (
        playerSpawns.size() > 1
        &&
        spawnIndex == lastSpawnIndex
        );

    lastSpawnIndex = spawnIndex;

    return playerSpawns[spawnIndex];
}

float Map::getDeathZoneY() const
{
    return deathZoneY;
}

float Map::getWorldWidth() const
{
    return worldWidth;
}

void Map::loadPlatformTexture(
    const std::string& texturePath
)
{
    platformTexture.loadFromFile(
        texturePath
    );

    platformTexture.setRepeated(
        true
    );
}
