#include "Map.h"
#include "Weapon.h"
#include <utility>

Map::Map(sf::Vector2u windowSize, int mapType)
{   
    this->windowSize = windowSize;

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

    platforms.clear();

    platforms.push_back(
        Platform(0.f, 950.f, 1920.f, 130.f)
    );

    platforms.push_back(
        Platform(300.f, 760.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(1200.f, 760.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(750.f, 600.f, 400.f, 40.f)
    );

    weapons.push_back(
        std::make_unique<Sword>(600.f, 400.f)
    );

    weapons.push_back(
        std::make_unique<Katana>(900.f, 300.f)
    );

    weapons.push_back(
        std::make_unique<Club>(1200.f, 400.f)
    );

    weapons.push_back(
        std::make_unique<Spear>(1500.f, 350.f)
    );
}

void Map::loadMap2()
{
    backgroundLayers.clear();

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

 
    platforms.clear();

    platforms.push_back(
        Platform(0.f, 1500.f, 3500.f, 150.f)
    );

    platforms.push_back(
        Platform(200.f, 1250.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(600.f, 1050.f, 350.f, 40.f)
    );

    platforms.push_back(
        Platform(1050.f, 850.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(1450.f, 1150.f, 600.f, 40.f)
    );

    platforms.push_back(
        Platform(1650.f, 850.f, 200.f, 40.f)
    );

    platforms.push_back(
        Platform(1450.f, 650.f, 200.f, 40.f)
    );

    platforms.push_back(
        Platform(1850.f, 650.f, 200.f, 40.f)
    );

    platforms.push_back(
        Platform(2450.f, 850.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(2850.f, 1050.f, 350.f, 40.f)
    );

    platforms.push_back(
        Platform(3200.f, 1250.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(1600.f, 400.f, 300.f, 40.f)
    );

    weapons.push_back(
        std::make_unique<Sword>(
            275.f,
            680.f
        )
    );

    weapons.push_back(
        std::make_unique<Sword>(
            350.f,
            1180.f
        )
    );

    weapons.push_back(
        std::make_unique<Katana>(
            1700.f,
            780.f
        )
    );

    weapons.push_back(
        std::make_unique<Club>(
            2600.f,
            780.f
        )
    );

    weapons.push_back(
        std::make_unique<Spear>(
            1750.f,
            330.f
        )
    );
}

void Map::loadMap3()
{
    backgroundLayers.clear();

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


    platforms.clear();

    platforms.push_back(
        Platform(0.f, 950.f, 1920.f, 130.f)
    );

    platforms.push_back(
        Platform(300.f, 760.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(1200.f, 760.f, 300.f, 40.f)
    );

    platforms.push_back(
        Platform(750.f, 600.f, 400.f, 40.f)
    );

    weapons.push_back(
        std::make_unique<Sword>(600.f, 400.f)
    );

    weapons.push_back(
        std::make_unique<Katana>(900.f, 300.f)
    );

    weapons.push_back(
        std::make_unique<Club>(1200.f, 400.f)
    );

    weapons.push_back(
        std::make_unique<Spear>(1500.f, 350.f)
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
