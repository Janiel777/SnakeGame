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
        vector<vector<int>>* matrix;
        ~EntityManager();
        void tick();
        void render();
        void checkCollisions();
        void keyPressed(int key);
        void deleteDruit(Fruit* f);
        void spawNewSnake(int mapX, int mapY, int mapW, int mapH, int squaresLength);
        void deleteFruits(int mapX, int mapY, int mapW, int mapH, int squaresLength);
        void deleteBounds();
};


