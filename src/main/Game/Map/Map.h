#pragma once
#include "ofMain.h"
#include "Entity.h"
#include "Bound.h"


class Map{
    private:
        int x, y, w, h;
        int squaresLength;
        int windowW = ofGetWidth();
        int windowH = ofGetHeight();
        vector<vector<int>> matrix;
        vector<Entity*> bounds;
    public:
        Map(int w, int h, int squaresLength);
        void render();
        void tick();
        
};


