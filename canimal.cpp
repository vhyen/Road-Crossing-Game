#include "canimal.h"

void CANIMAL::move() {
    aSprite.move(velocity, 0);
}

void CANIMAL::render(sf::RenderWindow* window) {
    window->draw(aSprite);
}

const sf::FloatRect CANIMAL::getBound() const {
    return aSprite.getGlobalBounds();
}

CDINOSAUR::CDINOSAUR(int level, float offsetY) {
    aTexture.loadFromFile("asset\\dino.png", sf::IntRect(5, 5, 15, 15));
    aSprite.setTexture(aTexture);
    aSprite.setScale(2.5, 2.5);
    velocity = 0.05 * level;
    aSprite.setPosition(-50, offsetY);
}

CBIRD::CBIRD(int level, float offsetY) {
    aTexture.loadFromFile("asset\\people.png", sf::IntRect(168, 128, 16, 16));
    aSprite.setTexture(aTexture);
    aSprite.setScale(1.3, 1.3);
    velocity = - 0.095;
    aSprite.setPosition(970, offsetY);
}




