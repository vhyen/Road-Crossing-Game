
#include "cpeople.h"

CPEOPLE::CPEOPLE() {
    pTexture.loadFromFile("asset\\people.png", sf::IntRect(6, 4, 12, 20));
    pSprite.setTexture(pTexture);
    pSprite.setPosition(470, 500);
    pSprite.setScale(1.5, 1.5);
    velocity = 0.2f;
}

void CPEOPLE::render(sf::RenderWindow* window) {
    window->draw(pSprite);
}

void CPEOPLE::resetState() {
    pSprite.setPosition(470, 500);
}

void CPEOPLE::moveLeft() {
    if (pSprite.getGlobalBounds().left <= 1) return;
    pSprite.move(-velocity, 0);
}

void CPEOPLE::moveRight() {
    if (pSprite.getGlobalBounds().left + pSprite.getGlobalBounds().width >= 960) return;
    pSprite.move(+velocity, 0); 
}

void CPEOPLE::moveUp() {
    if (pSprite.getGlobalBounds().top <= 0) return;
    pSprite.move(0, -velocity);
}

void CPEOPLE::moveDown() {
    if (pSprite.getGlobalBounds().top + pSprite.getGlobalBounds().height >= 540) return;
    pSprite.move(0, +velocity);
}

bool CPEOPLE::isImpact(CVEHICLE* enemy) {
    if (pSprite.getGlobalBounds().intersects(enemy->getBound())) {
        return true;
    }
    return false;
}

bool CPEOPLE::isImpact(CANIMAL* enemy) {
    if (pSprite.getGlobalBounds().intersects(enemy->getBound())) {
        return true;
    }
    return false;
}

bool CPEOPLE::isVictory() {
    if (pSprite.getGlobalBounds().top <= 35) return true;
    return false;
}