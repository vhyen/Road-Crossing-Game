#ifndef CGAME_H_
#define CGAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Network.hpp>


#include "canimal.h"
#include "canimal.cpp"
#include "cvehicle.h"
#include "cvehicle.cpp"
#include "cpeople.h"
#include "cpeople.cpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CGAME {
    public:
    CGAME(sf::RenderWindow*);
    
    int run(int);
    void saveGame(int, sf::RenderWindow*);

    private:
    
    std::vector<CTRUCK> truckFlow;
    std::vector<CCAR> carFlow;
    std::vector<CBIRD> birdFlow;
    std::vector<CDINOSAUR> dinoFlow;
    CPEOPLE player;

    sf::Texture scrInstruction, scrSettings, scrPause, scrDeadScene, scrEnd, scrSave;
    sf::Texture scrWc1, scrWc2, scrWc3, scrGame1, scrGame2, scrGame3;
    sf::Sprite sprInstruction, sprSettings, sprPause, sprDeadScene, sprEnd, sprSave;
    sf::Sprite sprWc1, sprWc2, sprWc3, sprGame1, sprGame2, sprGame3;

    sf::Sprite sprGame;
    sf::RenderWindow* win;
};


#endif