#ifndef CANIMAL_H_
#define CANIMAL_H_

/*
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Network.hpp>
*/

#include <iostream>
#include <vector>


class CANIMAL {
    protected:
    sf::Texture aTexture;
    sf::Sprite aSprite;
    float velocity;

    public:
    
    void move();
    void render(sf::RenderWindow*);
    const sf::FloatRect getBound() const;
};

class CDINOSAUR : public CANIMAL {

    public:
    CDINOSAUR(int, float);
};

class CBIRD : public CANIMAL {

    public:
    CBIRD(int, float);
};




#endif