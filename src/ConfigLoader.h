

#pragma once

#include <iostream>
#include <json.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>


class ConfigLoader {

private:
    std::fstream config_file;
    nlohmann::json CONFIG;

public:
    ConfigLoader(std::string config_file_path);
    ~ConfigLoader();

    std::string WINDOW_TITLE;
    uint WINDOW_WIDTH;
    uint WINDOW_HEIGHT;
    uint FRAME_RATE;
    sf::Color BACKGROUND_COLOR;
    int ANTIALIASING_LEVEL;
    float BALL_RADIUS;
    float BALL_SPEED;
    sf::Color BALL_COLOR;
    bool SHOW_COLLISION_SHAPES;
    float PAD_WIDTH;
    float PAD_HEIGHT;
    sf::Color PAD_COLOR;
    float PAD_SENSIVITY;
    sf::Vector2f PAD_COLLISION_MARGIN;
    sf::Vector2f WINDOW_COLLISION_PADDING;
    int SCORE_COUNTER_FONT_SIZE;
    sf::Color SCORE_COUNTER_COLOR;
    float ISLAND_WIDTH;
    float ISLAND_HEIGHT;
    sf::Color ISLAND_COLOR;
    sf::Vector2f ISLAND_COLLISION_MARGIN;
    float BALL_SPEED_MULTIPLIER;

};