#ifndef CVEHICLE_H_
#define CVEHICLE_H_

/*
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Network.hpp>
*/

#include <iostream>
#include <vector>

class TrafficLight {
    public:
    TrafficLight();
    void setPosition(float, float);
    void render(sf::RenderWindow*);
    void switchLight();
    bool isGreen();
    const sf::FloatRect getBound() const;

    private:
    sf::Texture GreenLight;
    sf::Texture RedLight;
    sf::Sprite  tlSprite;

    bool state;

};

class CVEHICLE {
    protected:
    sf::Texture vTexture;
    sf::Sprite vSprite;
    float velocity;
    bool canMove;

    public:
    void move();
    void render(sf::RenderWindow* );
    virtual void checkCollision(CVEHICLE*, TrafficLight*);
    const sf::FloatRect getBound() const;

};

class CCAR : public CVEHICLE {
    public:
    CCAR(int, float);
    void checkCollision(CVEHICLE*, TrafficLight*);
};

class CTRUCK : public CVEHICLE {
    public:
    CTRUCK(int, float);
    void checkCollision(CVEHICLE*, TrafficLight*);
};





#endif