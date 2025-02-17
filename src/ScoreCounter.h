

#pragma once

#include <SFML/Graphics.hpp>

#include "ConfigLoader.h"


class ScoreCounter {

private:
    sf::Font FONT_DIN_CONDENSED_BOLD;
    sf::Text COUNTER;
    int SCORE;

    const ConfigLoader& CONFIG;

public:
    ScoreCounter(ConfigLoader& config);
    ~ScoreCounter();

    void update();
    void draw(sf::RenderWindow& WINDOW);
    void score_up();

};