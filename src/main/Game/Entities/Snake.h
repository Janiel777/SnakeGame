#pragma once

#include "ofMain.h"
#include "Entity.h"
#include "Bound.h"
#include "Fruit.h"


enum MOVING{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Snake : public Entity{
    private:
        
        MOVING moving = RIGHT;
        int counter = 0;
        int speed = 6;
    public:
        vector<ofRectangle*> body;
        Snake(int x, int y, int w, int h);
        ~Snake();
        void render();
        void tick();
        void keyPressed(int key);
        void increaseSize();
        void updateCoordinates(int oldMapX, int oldMapY, int mapX, int mapY);
        int getSpeed(){return speed;}
        void setSpeed(int num){speed = num; counter = 0;}
        
};