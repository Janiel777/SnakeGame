#pragma once

#include "ofMain.h"
#include "Entity.h"


class Snake : public Entity{
    private:

    public:
        Snake(int x, int y, int w, int h) : Entity(x, y, w, h){}
        void render(){}
        
};