#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Snake.h"
#include "EntityManager.h"
#include "FruitSpawner.h"
#include "Button.h"



class Map{
    private:
        int x, y, w, h;
        int squaresLength;
        int windowW = ofGetWidth();
        int windowH = ofGetHeight();
        bool showHud = false;
        vector<vector<int>> matrix;
        EntityManager* em;
        FruitSpawner* fruitSpawner;

        Button* increasWidthButton;
        Button* decreaseWidthButton;
        Button* increasHeightButton;
        Button* decreaseHeightButton;
        Button* increasSnakeSpeedButton;
        Button* decreaseSnakeSpeedButton;
        Button* increaseFuitsButton;
        Button* decreaseFuitsButton;

        ofImage plusSign;
        ofImage minusSign;
        ofTrueTypeFont font;


    public:
        Map(int w, int h, int squaresLength);
        ~Map();
        void updateEntitiesCoordinates();
        void drawGrid();
        void drawHud();
        void render();
        void tick();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void mouseTracking(int x, int y);
        void reset();
        void changeMapDimensions();
        void deleteFruits();
        void deleteBounds();

        
};


