#include "cvehicle.h"

TrafficLight::TrafficLight() {
    RedLight.loadFromFile("asset\\traffic light.png", sf::IntRect(121, 0, 120, 191));
    GreenLight.loadFromFile("asset\\traffic light.png", sf::IntRect(0, 0, 120, 191));
    state = true;
    tlSprite.setTexture(GreenLight);
    tlSprite.setScale(0.15, 0.15);
}

void TrafficLight::setPosition(float x, float y) {
    tlSprite.setPosition(x, y);
}

void TrafficLight::render(sf::RenderWindow* window) {
    window->draw(tlSprite);
}

void TrafficLight::switchLight() {
    state = !state;
    if (state) 
        tlSprite.setTexture(GreenLight);
    else
        tlSprite.setTexture(RedLight);
}

bool TrafficLight::isGreen() {
    return state;
}

const sf::FloatRect TrafficLight::getBound() const {
    return tlSprite.getGlobalBounds();
}


void CVEHICLE::move() {
    if (canMove)
    vSprite.move(velocity, 0);
}

void CVEHICLE::render(sf::RenderWindow* window) {
    window->draw(vSprite);
}

void CVEHICLE::checkCollision(CVEHICLE* previous, TrafficLight* trl) {
    /*
    if (vSprite.getGlobalBounds().intersects(previous->getBound())
        || (!trl->isGreen() && vSprite.getGlobalBounds().intersects(trl->getBound()))) {
                canMove = false;
    }
    canMove = true;
    */
}

const sf::FloatRect CVEHICLE::getBound() const {
    return vSprite.getGlobalBounds();
}

CCAR::CCAR(int level, float offsetY) {
    vTexture.loadFromFile("asset\\car.png");
    vSprite.setTexture(vTexture);
    vSprite.setScale(0.07f, 0.07f);

    velocity = -0.07 * level;
    canMove = true;
    vSprite.setPosition(970, offsetY);
} 

void CCAR::checkCollision(CVEHICLE* previous, TrafficLight* trl) {
    if (!trl->isGreen() && vSprite.getGlobalBounds().intersects(trl->getBound())) {
        canMove = false;
    }
    else if (previous != nullptr && vSprite.getGlobalBounds().left  - 10 <= previous->getBound().left + previous->getBound().width) {
        canMove = false;
    }
    else
        canMove = true;
}

CTRUCK::CTRUCK(int level, float offsetY) {
    vTexture.loadFromFile("asset\\truck.png");
    vSprite.setTexture(vTexture);
    vSprite.setScale(0.2f, 0.2f);

    velocity = 0.05 * level;
    canMove = 1;
    vSprite.setPosition(-50, offsetY);
}

void CTRUCK::checkCollision(CVEHICLE* previous, TrafficLight* trl) {
    if (!trl->isGreen() && vSprite.getGlobalBounds().intersects(trl->getBound())) {
        canMove = false;
    }
    else if (previous != nullptr && vSprite.getGlobalBounds().left + vSprite.getGlobalBounds().width +10 >= previous->getBound().left) {
        canMove = false;
    }
    else
        canMove = true;
}