#pragma once
#include "ofMain.h"

class Button {
    
    public:
        Button();
        Button(int, int, int, int, string);
        Button(int, int, int, int, ofImage);
        void mousePressed(int x, int y);
        void mouseTracking(int x, int y);
        int getX();
        void setX(int x);
        int getY();
        void setY(int x);
        int getWidth();
        int getHeight();
        void tick();
        void render();
        bool isInButton();
        bool wasPressed();
        void reset();

    private:
        int xPos, yPos, width, height;
        ofImage buttonImage;
        ofImage clickedButtonImage;
        bool pressed = false;
        int pressedCounter = -1;
        string buttonText;
        bool inButton = false;
        float growFactor;
        int growX;
        int growY;
        int growW;
        int growH;
};