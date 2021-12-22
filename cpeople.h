#ifndef CPEOPLE_H_
#define CPEOPLE_H_


class CPEOPLE {

    public:
    CPEOPLE();
    void render(sf::RenderWindow*);
    void resetState();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool isImpact(CVEHICLE*);
    bool isImpact(CANIMAL*);
    bool isVictory();

    private:
    sf::Texture pTexture;
    sf::Sprite pSprite;
    float velocity;
};


#endif