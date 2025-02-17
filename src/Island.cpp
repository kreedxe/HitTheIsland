

#include "Island.h"


Island::Island(ConfigLoader& config):
CONFIG(config),
SHAPE(sf::Vector2f(CONFIG.ISLAND_WIDTH, CONFIG.ISLAND_HEIGHT)),
COLLISION_SHAPE(SHAPE.getSize() + CONFIG.ISLAND_COLLISION_MARGIN * 2.0f)
{

    // SHAPE.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - SHAPE.getSize().x / 2, CONFIG.WINDOW_HEIGHT / 40));
    SHAPE.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - SHAPE.getSize().x / 2, 0));
    SHAPE.setFillColor(CONFIG.ISLAND_COLOR);

    COLLISION_SHAPE.setPosition(SHAPE.getPosition() - CONFIG.ISLAND_COLLISION_MARGIN);
    COLLISION_SHAPE.setFillColor(sf::Color::Transparent);
    COLLISION_SHAPE.setOutlineColor(sf::Color::Red);
    COLLISION_SHAPE.setOutlineThickness(2.0f);

}

Island::~Island() {

}

void Island::update() {

}

void Island::draw(sf::RenderWindow& WINDOW) {
    WINDOW.draw(SHAPE);
    if (CONFIG.SHOW_COLLISION_SHAPES) {
        WINDOW.draw(COLLISION_SHAPE);
    }
}

sf::FloatRect Island::getCollisionShape() {
    return SHAPE.getGlobalBounds();
}