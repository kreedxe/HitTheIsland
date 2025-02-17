

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Ball.h"
#include "ConfigLoader.h"
#include "Pad.h"
#include "ScoreCounter.h"
#include "Island.h"


int main() 
{

    // LOAD CONFIG
    ConfigLoader CONFIG("../data/config.json");

    // CREATE WINDOW
    sf::ContextSettings CONTEXT_SETTINGS;
    CONTEXT_SETTINGS.antiAliasingLevel = CONFIG.ANTIALIASING_LEVEL;
    sf::RenderWindow WINDOW(sf::VideoMode({CONFIG.WINDOW_WIDTH, CONFIG.WINDOW_HEIGHT}), 
                            CONFIG.WINDOW_TITLE, sf::Style::Close, sf::State::Windowed, CONTEXT_SETTINGS);

    // SET FRAME RATE LIMIT
    WINDOW.setFramerateLimit(CONFIG.FRAME_RATE);
    
    // CREATE PAD
    Pad pad(CONFIG);

    // CREATE SCORE COUNTER
    ScoreCounter SCORE_COUNTER(CONFIG);

    // CREATE ISLAND
    Island ISLAND(CONFIG);

    // CREATE BALL
    Ball ball(CONFIG, SCORE_COUNTER);

    // CREATE WINDOW COLLISION SHAPE
    sf::RectangleShape WINDOW_COLLISION_SHAPE(sf::Vector2f(CONFIG.WINDOW_WIDTH, CONFIG.WINDOW_HEIGHT) - CONFIG.WINDOW_COLLISION_PADDING * 2.0f);
    WINDOW_COLLISION_SHAPE.setPosition(CONFIG.WINDOW_COLLISION_PADDING);
    WINDOW_COLLISION_SHAPE.setFillColor(sf::Color::Transparent);
    WINDOW_COLLISION_SHAPE.setOutlineColor(sf::Color::Red);
    WINDOW_COLLISION_SHAPE.setOutlineThickness(2.0f);


    // CREATE CLOCK TO CALCULATE DeltaTime
    sf::Clock CLOCK;
    float DeltaTime;


    // MAIN LOOP
    while (WINDOW.isOpen()) 
    {

        //CHECK FOR CLOSE
        while (const std::optional event = WINDOW.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            WINDOW.close();
        }


        // CALCULATE DeltaTime
        DeltaTime = std::round(CLOCK.restart().asMicroseconds() / 16666.0f * 10.0f) / 10.0f;


        // CLEAR WINDOW AND FILL WITH COLOR
        WINDOW.clear(CONFIG.BACKGROUND_COLOR);


        // UPDATE
        pad.update();
        ball.update(DeltaTime, pad.getCollisionShape(), ISLAND.getCollisionShape());
        SCORE_COUNTER.update();
        ISLAND.update();


        // DRAW
        ball.draw(WINDOW);
        pad.draw(WINDOW);
        if (CONFIG.SHOW_COLLISION_SHAPES) {
            WINDOW.draw(WINDOW_COLLISION_SHAPE);
        }
        ISLAND.draw(WINDOW);
        SCORE_COUNTER.draw(WINDOW);


        // UPDATE WINDOW
        WINDOW.display();

    }
    
    return 0;
}