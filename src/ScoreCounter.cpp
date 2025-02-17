

#include "ScoreCounter.h"


ScoreCounter::ScoreCounter(ConfigLoader& config):
FONT_DIN_CONDENSED_BOLD("../data/fonts/DIN Condensed Bold.ttf"),
COUNTER(FONT_DIN_CONDENSED_BOLD, "0", config.SCORE_COUNTER_FONT_SIZE),
CONFIG(config),
SCORE(0)
{
    
    COUNTER.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - COUNTER.getGlobalBounds().size.x / 2, 
                                    CONFIG.WINDOW_HEIGHT - CONFIG.WINDOW_HEIGHT / 9));
    COUNTER.setFillColor(CONFIG.SCORE_COUNTER_COLOR);

}

ScoreCounter::~ScoreCounter() {

}

void ScoreCounter::update() {

}

void ScoreCounter::draw(sf::RenderWindow& WINDOW) {
    WINDOW.draw(COUNTER);
}

void ScoreCounter::score_up() {
    SCORE += 1;
    COUNTER.setString(std::to_string(SCORE));
    COUNTER.setPosition(sf::Vector2f(CONFIG.WINDOW_WIDTH / 2 - COUNTER.getGlobalBounds().size.x / 2, 
                                    CONFIG.WINDOW_HEIGHT - CONFIG.WINDOW_HEIGHT / 9));
}