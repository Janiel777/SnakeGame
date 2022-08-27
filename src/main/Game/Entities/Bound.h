#pragma once
#include "ofMain.h"
#include "Entity.h"

class Bound : public Entity{
    private:
        
    public:
        Bound(int x, int y, int w, int h);
        void render();
        void tick();
        
};


