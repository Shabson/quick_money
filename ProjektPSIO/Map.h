#pragma once
#include <vector>
#include <SFML/Graphics.hpp>    
#include "Platform.h"
#include "ParallaxLayer.h"

class Map
{

private:
    std::vector<Platform> platforms;
    std::vector<sf::Vector2f> playerSpawns;
    std::vector<sf::Vector2f> weaponSpawns;
    std::vector<ParallaxLayer> backgroundLayers;
    sf::Sprite background;
public:
    Map();

    void loadMap1() {
        backgroundLayers.push_back(
            ParallaxLayer(".\assets\textures\parallax-mountain-bg.png", 0.2f)
        );
        // TODO!!!
        backgroundLayers.push_back(
            ParallaxLayer("assets/bg_mid.png", 0.5f)
        );

        backgroundLayers.push_back(
            ParallaxLayer("assets/bg_front.png", 0.8f)
        );
        backgroundLayers.push_back(
            ParallaxLayer("assets/bg_front.png", 0.8f)
        );
        backgroundLayers.push_back(
            ParallaxLayer("assets/bg_front.png", 0.8f)
        );
    };
    
    void draw(sf::RenderWindow& window) {
        for (auto& layer : backgroundLayers)
        {
            layer.draw(window);
        }
    };

    std::vector<Platform>& getPlatforms();

    void update(float cameraX);
};