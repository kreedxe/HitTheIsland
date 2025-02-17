

#include "Ball.h"


Ball::Ball(ConfigLoader& config, ScoreCounter& score_counter):
CONFIG(config),
SHAPE(CONFIG.BALL_RADIUS),
COLLISION_SHAPE(sf::Vector2f(CONFIG.BALL_RADIUS * 2, CONFIG.BALL_RADIUS * 2)),
RADIUS(config.BALL_RADIUS),
SPEED(config.BALL_SPEED),
VELOCITY(0.5f, 1),
SCORE_COUNTER(score_counter),
PAD_SOUNDBUFFER("../data/sounds/impactGlass_heavy_000.ogg"),
ISLAND_SOUNDBUFFER("../data/sounds/impactGlass_light_000.ogg"),
TOUCH_SOUNDBUFFER("../data/sounds/impactGlass_medium_000.ogg"),
PAD_SOUND(PAD_SOUNDBUFFER),
ISLAND_SOUND(ISLAND_SOUNDBUFFER),
TOUCH_SOUND(TOUCH_SOUNDBUFFER)
{

    SHAPE.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - RADIUS, CONFIG.WINDOW_HEIGHT - CONFIG.WINDOW_HEIGHT / 3));
    SHAPE.setFillColor(CONFIG.BALL_COLOR);

    COLLISION_SHAPE.setPosition(SHAPE.getPosition());
    COLLISION_SHAPE.setFillColor(sf::Color::Transparent);
    COLLISION_SHAPE.setOutlineColor(sf::Color::Red);
    COLLISION_SHAPE.setOutlineThickness(2.0f);

}

Ball::~Ball() {
    
}

void Ball::update(float DeltaTime, sf::FloatRect padCollisionShape, sf::FloatRect IslandCollisionShape) {
    if (FAILED) {
        return;
    }

    // CHECK FOR COLLISION WITH ISLAND
    if (COLLISION_SHAPE.getPosition().y < IslandCollisionShape.position.y + IslandCollisionShape.size.y &&
        COLLISION_SHAPE.getPosition().x < IslandCollisionShape.position.x + IslandCollisionShape.size.x &&
        IslandCollisionShape.position.x < COLLISION_SHAPE.getPosition().x + COLLISION_SHAPE.getSize().x &&
        VELOCITY.y < 0) {

        VELOCITY.y = (VELOCITY.y < 0) ? -VELOCITY.y : VELOCITY.y;
        SCORE_COUNTER.score_up();
        SPEED *= CONFIG.BALL_SPEED_MULTIPLIER;
        ISLAND_SOUND.play();
    }
    // else if (COLLISION_SHAPE.getPosition().y < IslandCollisionShape.position.y + IslandCollisionShape.size.y &&
    //     COLLISION_SHAPE.getPosition().x < IslandCollisionShape.position.x + IslandCollisionShape.size.x &&
    //     VELOCITY.x < 0) {

    //     VELOCITY.x = (VELOCITY.y < 0) ? -VELOCITY.y : VELOCITY.y;
    //     SCORE_COUNTER.score_up();
    // }
    // else if (COLLISION_SHAPE.getPosition().y < IslandCollisionShape.position.y + IslandCollisionShape.size.y &&
    //     COLLISION_SHAPE.getPosition().x + COLLISION_SHAPE.getSize().x > IslandCollisionShape.position.x &&
    //     VELOCITY.x > 0) {

    //     VELOCITY.x = (VELOCITY.y > 0) ? -VELOCITY.y : VELOCITY.y;
    //     SCORE_COUNTER.score_up();
    // }

    // CHECK FOR COLLISION WITH SCREEN SIDES
    if (COLLISION_SHAPE.getPosition().y < CONFIG.WINDOW_COLLISION_PADDING.y && VELOCITY.y < 0) {
        VELOCITY.y = (VELOCITY.y < 0) ? -VELOCITY.y : VELOCITY.y;
        TOUCH_SOUND.play();
    }
    if (COLLISION_SHAPE.getPosition().y + COLLISION_SHAPE.getSize().y > CONFIG.WINDOW_HEIGHT - CONFIG.WINDOW_COLLISION_PADDING.y) {
        VELOCITY.y = (VELOCITY.y > 0) ? -VELOCITY.y : VELOCITY.y;
        VELOCITY.y = 0;
        VELOCITY.x = 0;
        return;
    }
    if (COLLISION_SHAPE.getPosition().x < CONFIG.WINDOW_COLLISION_PADDING.x) {
        VELOCITY.x = (VELOCITY.x < 0) ? -VELOCITY.x : VELOCITY.x;
        TOUCH_SOUND.play();
    }
    if (COLLISION_SHAPE.getPosition().x + COLLISION_SHAPE.getSize().x > CONFIG.WINDOW_WIDTH - CONFIG.WINDOW_COLLISION_PADDING.x) {
        VELOCITY.x = (VELOCITY.x > 0) ? -VELOCITY.x : VELOCITY.x;
        TOUCH_SOUND.play();
    }

    // CHECK FOR COLLISION WITH PAD (TOP)
    if (SHAPE.getPosition().x + RADIUS * 2 > padCollisionShape.position.x &&
        SHAPE.getPosition().x < padCollisionShape.position.x + padCollisionShape.size.x &&
        SHAPE.getPosition().y + RADIUS * 2 > padCollisionShape.position.y &&
        SHAPE.getPosition().y < padCollisionShape.position.y + padCollisionShape.size.y && VELOCITY.y > 0) {

            float collision_point = 1;

            if (SHAPE.getPosition().x + RADIUS == padCollisionShape.position.x + padCollisionShape.size.x / 2) {
                collision_point = 0;

            } else if (SHAPE.getPosition().x + RADIUS < padCollisionShape.position.x + padCollisionShape.size.x / 2) {
                collision_point = (SHAPE.getPosition().x + RADIUS - padCollisionShape.position.x) / (padCollisionShape.size.x / 2) * -1;

            } else if (SHAPE.getPosition().x + RADIUS > padCollisionShape.position.x + padCollisionShape.size.x / 2) {
                collision_point = (SHAPE.getPosition().x + RADIUS - (padCollisionShape.position.x + padCollisionShape.size.x / 2)) / (padCollisionShape.size.x / 2);
                
            }

            VELOCITY.y *= -1;
            VELOCITY.x = collision_point * 1;
            PAD_SOUND.play();
    }
    
    // NORMALIZE VELOCITY
    float magnitude = std::sqrt(VELOCITY.x * VELOCITY.x + VELOCITY.y * VELOCITY.y);
    VELOCITY.x /= magnitude;
    VELOCITY.y /= magnitude;

    // MOVE THE BALL
    SHAPE.setPosition(sf::Vector2f(SHAPE.getPosition().x + VELOCITY.x * SPEED * DeltaTime,
                                   SHAPE.getPosition().y + VELOCITY.y * SPEED * DeltaTime));

    // UPDATE COLLISION SHAPE
    COLLISION_SHAPE.setPosition(SHAPE.getPosition());

}

void Ball::draw(sf::RenderWindow& WINDOW) {
    WINDOW.draw(SHAPE);
    
    if (CONFIG.SHOW_COLLISION_SHAPES)
        WINDOW.draw(COLLISION_SHAPE);
}