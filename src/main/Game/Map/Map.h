#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Snake.h"
#include "EntityManager.h"
#include "FruitSpawner.h"
#include "Button.h"
#include <list>


class Map{
    private:
        int x, y, w, h;
        int squaresLength;
        int windowW = ofGetWidth();
        int windowH = ofGetHeight();

        bool showHud = false;
        bool searching = false;

        vector<vector<int>>* matrix;
        vector<vector<int>>* matrixCopy;

        list<list<int>> path;
        list<list<int>> paths;
    
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
        void drawMatrix(vector<vector<int>>*);
        void setFruitInMatrix();
        void setSnakeInMatrix();
        void BFStraversal();
        void drawPaths();

        
};


