#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include "Platform.h"
#include "ParallaxLayer.h"
#include "Weapon.h"
#include <memory>

class Map
{
private:
    std::vector<Platform> platforms;
    std::vector<sf::Vector2f> playerSpawns;
    std::vector<sf::Vector2f> weaponSpawns;
    std::vector<std::unique_ptr<Weapon>> weapons;
    std::vector<std::unique_ptr<ParallaxLayer>> backgroundLayers;
    sf::Vector2u windowSize;
    sf::Clock weaponSpawnClock;
    std::mt19937 randomGenerator;
    float deathZoneY;
    float worldWidth;

    sf::Texture platformTexture;

    void loadPlatformTexture(
        const std::string& texturePath
    );

public:
    Map(
        sf::Vector2u windowSize,
        int mapType
    );

    void loadMap1();
    void loadMap2();
	void loadMap3();

    void draw(
        sf::RenderWindow& window,
        const sf::View& camera
    );



    std::vector<Platform>& getPlatforms();
    std::vector<std::unique_ptr<Weapon>>& getWeapons();
    void addWeapon(std::unique_ptr<Weapon> weapon);
    void updateWeaponSpawner();
    void spawnRandomWeapon();
    sf::Vector2f getPlayerSpawn(int playerIndex) const;
    float getDeathZoneY() const;
    float getWorldWidth() const;

};
