#pragma once
#include "ofMain.h"
#include "Entity.h"

class Fruit : public Entity{
    private:
        
    public:
        Fruit(int x, int y, int w, int h);
        ~Fruit();
        void render();
        void tick();
        
};