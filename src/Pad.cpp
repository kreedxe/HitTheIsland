

#include "Pad.h"


Pad::Pad(ConfigLoader& config):
CONFIG(config),
SHAPE(sf::Vector2f(CONFIG.PAD_WIDTH, CONFIG.PAD_HEIGHT)),
COLLISION_SHAPE(SHAPE.getSize() + CONFIG.PAD_COLLISION_MARGIN * 2.0f),
PAD_WIDTH(CONFIG.PAD_WIDTH),
PAD_HEIGHT(CONFIG.PAD_HEIGHT)
{
    SHAPE.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - PAD_WIDTH / 2, 
                    CONFIG.WINDOW_HEIGHT - CONFIG.WINDOW_HEIGHT / 5));

    SHAPE.setFillColor(CONFIG.PAD_COLOR);

    COLLISION_SHAPE.setPosition(SHAPE.getPosition() - CONFIG.PAD_COLLISION_MARGIN);
    COLLISION_SHAPE.setFillColor(sf::Color::Transparent);
    COLLISION_SHAPE.setOutlineColor(sf::Color::Red);
    COLLISION_SHAPE.setOutlineThickness(2.0f);
}

Pad::~Pad() {

}

void Pad::update() {

    // MOVE PAD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
        SHAPE.getPosition().x > 0) {

        SHAPE.setPosition(sf::Vector2f(SHAPE.getPosition().x - CONFIG.PAD_SENSIVITY, SHAPE.getPosition().y));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
        SHAPE.getPosition().x + SHAPE.getSize().x < CONFIG.WINDOW_WIDTH) {

        SHAPE.setPosition(sf::Vector2f(SHAPE.getPosition().x + CONFIG.PAD_SENSIVITY, SHAPE.getPosition().y));
    }
    COLLISION_SHAPE.setPosition(SHAPE.getPosition() - CONFIG.PAD_COLLISION_MARGIN);

}

void Pad::draw(sf::RenderWindow& WINDOW) {
    WINDOW.draw(SHAPE);

    if (CONFIG.SHOW_COLLISION_SHAPES) {
        WINDOW.draw(COLLISION_SHAPE);
    }
}

sf::FloatRect Pad::getCollisionShape() {
    return COLLISION_SHAPE.getGlobalBounds();
}