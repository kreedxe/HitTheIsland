

#pragma once

#include <SFML/Graphics.hpp>

#include "ConfigLoader.h"


class Island {

private:
    ConfigLoader& CONFIG;

    sf::RectangleShape SHAPE;
    sf::RectangleShape COLLISION_SHAPE;

public:
    Island(ConfigLoader& config);
    ~Island();

    void update();
    void draw(sf::RenderWindow& WINDOW);

    sf::FloatRect getCollisionShape();

};