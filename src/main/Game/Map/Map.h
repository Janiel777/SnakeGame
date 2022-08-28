#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Snake.h"
#include "EntityManager.h"
#include "FruitSpawner.h"


class Map{
    private:
        int x, y, w, h;
        int squaresLength;
        int windowW = ofGetWidth();
        int windowH = ofGetHeight();
        vector<vector<int>> matrix;
        EntityManager* em;
        FruitSpawner* fruitSpawner;
    public:
        Map(int w, int h, int squaresLength);
        ~Map();
        void render();
        void tick();
        void keyPressed(int key);
        
};


