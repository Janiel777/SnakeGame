#pragma once
#include "ofMain.h"
#include "Bound.h"
#include "Fruit.h"
#include "Snake.h"



class EntityManager{
    public:
        vector<Bound*> bounds;
        vector<Fruit*> fruits;
        Snake* snake;
        ~EntityManager();
        void tick();
        void render();
        void checkCollisions();
        void keyPressed(int key);
};


