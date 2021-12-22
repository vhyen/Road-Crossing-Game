#include "cgame.h"

CGAME::CGAME(sf::RenderWindow* _win) { //CHECKED    
    
    win = _win;

    scrInstruction.loadFromFile("asset\\instruction.png");
    sprInstruction.setTexture(scrInstruction);
    sprInstruction.setScale(0.375, 0.375);

    scrPause.loadFromFile("asset\\pause.png");
    sprPause.setTexture(scrPause);
    sprPause.setScale(0.375, 0.375);

    scrSave.loadFromFile("asset\\save.png");
    sprSave.setTexture(scrSave);
    sprSave.setScale(0.375, 0.375);

    scrSettings.loadFromFile("asset\\settings.png");
    sprSettings.setTexture(scrSettings);
    sprSettings.setScale(0.375, 0.375);

    scrDeadScene.loadFromFile("asset\\hitted.png");
    sprDeadScene.setTexture(scrDeadScene);
    sprDeadScene.setScale(0.375, 0.375);

    scrEnd.loadFromFile("asset\\DEAD.png");
    sprEnd.setTexture(scrEnd);
    sprEnd.setScale(0.375, 0.375);

    scrWc1.loadFromFile("asset\\welcomelv1.png");
    sprWc1.setTexture(scrWc1);
    sprWc1.setScale(0.375, 0.375);

    scrWc2.loadFromFile("asset\\welcomelv2.png");
    sprWc2.setTexture(scrWc2);
    sprWc2.setScale(0.375, 0.375);

    scrWc3.loadFromFile("asset\\welcomelv3.png");
    sprWc3.setTexture(scrWc3);
    sprWc3.setScale(0.375, 0.375);

    scrGame1.loadFromFile("asset\\level1.png");
    sprGame1.setTexture(scrGame1);
    sprGame1.setScale(0.375, 0.375);

    scrGame2.loadFromFile("asset\\level2.png");
    sprGame2.setTexture(scrGame2);
    sprGame2.setScale(0.375, 0.375);

    scrGame3.loadFromFile("asset\\level3.png");
    sprGame3.setTexture(scrGame3);
    sprGame3.setScale(0.375, 0.375);

}

int CGAME::run(int level) {
    if (level > 3) return 0;
    win->clear();
    switch (level) {
        case 1: win->draw(sprWc1); sprGame = sprGame1;  break;
        case 2: win->draw(sprWc2); sprGame = sprGame2; break;
        case 3: win->draw(sprWc3); sprGame = sprGame3; break;
    }
    win->display();

    // OBJECTS SET UP STATE
    CTRUCK truck(level, 115);
    CCAR car(level, 350);
    CBIRD bird(level, 180);
    CDINOSAUR dino(level, 260);
    int time = 0;
    TrafficLight trl1, trl2;
    trl1.setPosition(700, 100);
    trl2.setPosition(200, 330);

    birdFlow.clear(); 
    dinoFlow.clear(); 
    carFlow.clear();
    truckFlow.clear();

    birdFlow.push_back(bird);
    dinoFlow.push_back(dino);
    carFlow.push_back(car);
    truckFlow.push_back(truck);

    player.resetState();

    bool startMove = false;
    bool dead = false;

    while (true) { 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
    }

    while(true) {

        win->clear();
        win->draw(sprGame);
        player.render(win);
        for (int i = 0; i < dinoFlow.size(); i++) {
            dinoFlow[i].move();
            dinoFlow[i].render(win);
            if (player.isImpact(&dinoFlow[i])) dead = true;
        }
        for(int i = 0; i < birdFlow.size(); i++) {
            birdFlow[i].move(); 
            birdFlow[i].render(win);
            if (player.isImpact(&birdFlow[i])) dead = true;
        }
        for (int i = 0; i < carFlow.size(); i++) {
            if (i == carFlow.size() - 1) carFlow[i].checkCollision(nullptr, &trl2);
            else carFlow[i].checkCollision(&carFlow[i+1], &trl2);
            carFlow[i].move(); 
            carFlow[i].render(win);
            if (player.isImpact(&carFlow[i])) dead = true;
        }
        for (int i = 0; i < truckFlow.size(); i++) {
            if (i == truckFlow.size() - 1) truckFlow[i].checkCollision(nullptr, &trl1);
            else truckFlow[i].checkCollision(&truckFlow[i+1], &trl1);
            truckFlow[i].move();
            truckFlow[i].render(win);
            if (player.isImpact(&truckFlow[i])) dead = true;
        }
        trl1.render(win);
        trl2.render(win);
        win->display();

        if (dead) {
            win->clear();
            win->draw(sprDeadScene);
            win->display();
            while(true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
            }
            win->clear();
            win->draw(sprEnd);
            win->display();
            while (true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) return 1;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) return 0;
            }
        }

        time++;     //spawn enemies
        if (time % (3000/level) == 0) {
            birdFlow.insert(birdFlow.begin(), bird);
            dinoFlow.insert(dinoFlow.begin(), dino);
        }
        if (time % (4800/level) == 0) {
            carFlow.insert(carFlow.begin(), car);
            truckFlow.insert(truckFlow.begin(), truck);
        }
        if (time % 5000 == 0) trl2.switchLight();
        if (time % 4500 == 0) trl1.switchLight();
        
        if (truckFlow[truckFlow.size() - 1].getBound().left >= 1285) truckFlow.pop_back();
        if (dinoFlow[dinoFlow.size() - 1].getBound().left >= 970) dinoFlow.pop_back();
        if (birdFlow[birdFlow.size() - 1].getBound().left <= -50) birdFlow.pop_back();
        if (carFlow[carFlow.size() - 1].getBound().left <= -50) carFlow.pop_back();

        if (startMove) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.moveRight();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.moveUp();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.moveDown();
        }
        if (player.isVictory()) return 2;
        if (truckFlow.size() > 4) startMove = true;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            while (true) {
                win->clear();
                win->draw(sprPause);
                win->display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) break;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { //INSTRUCTION
                    win->clear();
                    win->draw(sprInstruction);
                    win->display();
                    while (true) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { //SETTINGS
                    win->clear();
                    win->draw(sprSettings);
                    win->display();
                    while(true) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) return 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { //SAVE GAME
            saveGame(level, win);
            win->clear();
            win->draw(sprSave);
            win->display();
            while (true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) return 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) return 3;  // return main to load and restart game
        
    }
}

int loadGame (sf::RenderWindow* win) {
                
                std::cout << "\nLoadGame\n";
                int lv = 1;
                
                win->clear();
                sf::Font font;
                font.loadFromFile("asset\\myfont.ttf");
                sf::Event evnt;
                sf::String filename;
                sf::Text playerInput;
                playerInput.setFont(font);
                playerInput.setCharacterSize(30);
                playerInput.setPosition(400, 250);

                sf::Texture scrLoad; scrLoad.loadFromFile("asset\\loadgame.png");
                sf::Sprite sprLoad(scrLoad);
                sprLoad.setScale(0.375, 0.375);

                std::string mFilename;

                
                    bool toBreak = false;
                    int i = 0;
                    while(win->pollEvent(evnt) && i < 10000) {
                        if(evnt.type == sf::Event::TextEntered) {  }
                        i++;
                    }
                    while(true) {
                        win->clear();
                        win->draw(sprLoad);
                        win->draw(playerInput);
                        win->display();
                    while(win->pollEvent(evnt)) {
                        
                        if(evnt.type == sf::Event::TextEntered) {
                            if (evnt.text.unicode == 46 || (evnt.text.unicode > 60 && evnt.text.unicode < 123)) {
                                filename += evnt.text.unicode;
                                mFilename += evnt.text.unicode;
                                playerInput.setString(filename);
                            }
                            
                        }
                        
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            toBreak = true;
                            break;
                        }
                    }
                    if (toBreak) break;
                }
                //win.close();
                std::ifstream fin;
                fin.open(mFilename, std::ios::binary);
                if (fin.is_open()) {
                    fin.read((char*)&lv, sizeof(int));
                } else std::cout << "Cannot open file \n";
                fin.close();
      return lv;          
}

void CGAME::saveGame (int level, sf::RenderWindow*win) {
    std::cout << "\nSaveGame\n";
                
                win->clear();
                sf::Font font;
                font.loadFromFile("asset\\myfont.ttf");
                sf::Event evnt;
                sf::String filename;
                sf::Text playerInput;
                playerInput.setFont(font);
                playerInput.setCharacterSize(30);
                playerInput.setPosition(400, 250);

                sf::Texture scrSave; scrSave.loadFromFile("asset\\savegame.png");
                sf::Sprite sprSave(scrSave);
                sprSave.setScale(0.375, 0.375);

                std::string mFilename;

                for (int i = 0; i < 10000; i++) {
                    win->pollEvent(evnt);
                }
                int toBreak = false;
                while (true) {
                    win->clear();
                    win->draw(sprSave);
                    win->draw(playerInput);
                    win->display();
                    while(win->pollEvent(evnt)) {
                         
                        if(evnt.type == sf::Event::TextEntered) {
                            if (evnt.text.unicode == 46 || (evnt.text.unicode > 60 && evnt.text.unicode < 123)) {
                                filename += evnt.text.unicode;
                                mFilename += evnt.text.unicode;
                                playerInput.setString(filename);
                            }
                           
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            toBreak = true;
                            break;
                        }
                    }
                    if (toBreak) break;
                }

            std::ofstream fout;
            fout.open(mFilename, std::ios::binary);
            if (fout.is_open()) {
                fout.write((char*)&level, sizeof(int));
            }
            fout.close();
        return;
}


/*
compile
g++ -c main.cpp -I"C:\Users\Administrator\Documents\SFML-2.5.1\include" -I"D:\CS202\GameHandle"
g++ main.o -o main -L"C:\Users\Administrator\Documents\SFML-2.5.1\lib" -L"D:\CS202\GameHandle" -lsfml-graphics -lsfml-window -lsfml-system


*/