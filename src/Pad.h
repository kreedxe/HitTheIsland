

#pragma once

#include <SFML/Graphics.hpp>

#include "ConfigLoader.h"


class Pad {

private:
    ConfigLoader& CONFIG;

    sf::RectangleShape SHAPE;
    sf::RectangleShape COLLISION_SHAPE;

    float PAD_WIDTH;
    float PAD_HEIGHT;

public:
    Pad(ConfigLoader& config);
    ~Pad();

    void update();
    void draw(sf::RenderWindow& WINDOW);
    sf::FloatRect getCollisionShape();
};