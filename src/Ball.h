

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ConfigLoader.h"
#include "ScoreCounter.h"


class Ball {


private:
    ConfigLoader& CONFIG;

    sf::CircleShape SHAPE;
    sf::RectangleShape COLLISION_SHAPE;

    bool COLLIDED = false;

    int RADIUS;
    float SPEED;

    sf::Vector2f VELOCITY;

    ScoreCounter& SCORE_COUNTER;

    sf::SoundBuffer PAD_SOUNDBUFFER;
    sf::SoundBuffer ISLAND_SOUNDBUFFER;
    sf::SoundBuffer TOUCH_SOUNDBUFFER;

    sf::Sound PAD_SOUND;
    sf::Sound ISLAND_SOUND;
    sf::Sound TOUCH_SOUND;

    bool FAILED = false;

public:
    Ball(ConfigLoader& config, ScoreCounter& score_counter);
    ~Ball();

    void update(float DeltaTime, sf::FloatRect padCollisionShape, sf::FloatRect IslandCollisionShape);
    void draw(sf::RenderWindow& WINDOW);

};