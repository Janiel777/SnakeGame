#pragma once

#include "ofMain.h"

class Entity{
    protected:
        int x, y, w, h;

    public:
        Entity(int x, int y, int w, int h);
        virtual void render(){ofDrawRectangle(x,y,w,h);}
        virtual void tick(){}
        int getX(){return x;}
        int getY(){return y;}
        int getW(){return w;}
        int getH(){return y;}
        void setX(int num){x = num;}
        void setY(int num){y = num;}
        
};


