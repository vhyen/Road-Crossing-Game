

#include "cgame.h"
#include "cgame.cpp"


int main() {
        
        sf::RenderWindow window(sf::VideoMode(960, 540), "Game");

        window.clear();
        sf::Texture scrWelcome;
        scrWelcome.loadFromFile("asset\\welcome.png");
        sf::Sprite sprWelcome(scrWelcome);
        sprWelcome.setScale(0.375, 0.375);
        window.draw(sprWelcome);
        window.display();

        // Load other things
        sf::Texture scrMenu; 
        scrMenu.loadFromFile("asset\\menu.png");
        sf::Sprite sprMenu(scrMenu);
        sprMenu.setScale(0.375, 0.375);
        sprMenu.setPosition(0, 0);

        sf::Texture scrSettings; 
        scrSettings.loadFromFile("asset\\settings.png");
        sf::Sprite sprSettings(scrSettings);
        sprSettings.setScale(0.375, 0.375);
        sprSettings.setPosition(0, 0);
        
        sf::Texture scrInstruction; 
        scrInstruction.loadFromFile("asset\\instruction.png");
        sf::Sprite sprInstruction(scrInstruction);
        sprInstruction.setScale(0.375, 0.375);
        sprInstruction.setPosition(0, 0);

        sf::Texture scrEscape; 
        scrEscape.loadFromFile("asset\\Escape.png");
        sf::Sprite sprEscape(scrEscape);
        sprEscape.setScale(0.375, 0.375);
        sprEscape.setPosition(0, 0);

        sf::Texture scrFinish; 
        scrFinish.loadFromFile("asset\\Finished.png");
        sf::Sprite sprFinish(scrFinish);
        sprFinish.setScale(0.375, 0.375);
        sprFinish.setPosition(0, 0);
    
     
    CGAME game(&window);
    
        int level;
        window.clear();
        window.draw(sprMenu);
        window.display();

    while (window.isOpen()) {
        window.clear();
        window.draw(sprMenu);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // NEW GAME
            level = 1;
            while (level < 4) {
                int key = game.run(level);
                if (key == 0) { 
                    
                    break;
                }
                else if (key == 1) continue;
                else if (key == 2) {
                    level++;
                    if (level == 4) {
                        window.clear(); window.draw(sprEscape); window.display();
                        while (true) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
                        }
                        window.clear(); window.draw(sprFinish); window.display();
                        while (true) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
                        }
                        window.clear();
                        window.draw(sprMenu);
                        window.display();
                        break;
                    }
                }
                else if (key == 3) { 
                        level = loadGame(&window);
                    }
                }
            }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {  // CONTINUE GAME
                level = loadGame(&window);
                
                while (level < 4) {
                int key = game.run(level);
                if (key == 0) { 
                    //window.clear();
                    //window.draw(sprMenu);
                    //window.display();
                    break;
                }
                else if (key == 1) continue;
                else if (key == 2) {
                    level++;
                
                    if (level == 4) {
                    window.clear(); window.draw(sprEscape); window.display();
                    while (true) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
                    }
                    window.clear(); window.draw(sprFinish); window.display();
                    while (true) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
                    }
                    //window.clear();
                    //window.draw(sprMenu);
                    //window.display();
                    break;
                    }
                }
                else if (key == 3) { //LOAD GAME
                        level = loadGame(&window);
                }
            }
        
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {   //INSTRUCTION
            window.clear();
            window.draw(sprInstruction);
            window.display();
            while (true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
            }
            //window.clear();
            //window.draw(sprMenu);
            //window.display();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {   //SETTINGS
            window.clear();
            window.draw(sprSettings);
            window.display();
            while (true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) break;
            }
            //window.clear();
            //window.draw(sprMenu);
            //window.display();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) window.close();    //EXIT
       
    }
    
    return 0;
}


/*
compile
g++ -c main.cpp -I"C:\Users\Administrator\Documents\SFML-2.5.1\include" -I"D:\CS202\GameHandle"
g++ main.o -o main -L"C:\Users\Administrator\Documents\SFML-2.5.1\lib" -L"D:\CS202\GameHandle" -lsfml-graphics -lsfml-window -lsfml-system
*/