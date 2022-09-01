#include "Button.h"
Button::Button(){
   this->xPos = ofGetWidth()/2;
    this->yPos = ofGetHeight()/2;
    this->width = 64;
    this->height = 20; 
}
Button::Button(int xPos, int yPos, int width, int height, string buttonText){
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->buttonText = buttonText;
    growFactor = .15;
    growX = xPos - (width*growFactor)/2;
    growY = yPos - (height*growFactor)/2;
    growW = width + width*growFactor;
    growH = height + height*growFactor;
}

Button::Button(int xPos, int yPos, int width, int height, ofImage buttonImage){
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->buttonImage = buttonImage;
    this->buttonText = "";
    growFactor = .15;
    growX = xPos - (width*growFactor)/2;
    growY = yPos - (height*growFactor)/2;
    growW = width + width*growFactor;
    growH = height + height*growFactor;
}

void Button::reset(){
    pressed = false;
}
void Button::tick(){
    if(pressedCounter >= 0) pressedCounter--;

}

void Button::mousePressed(int x, int y){
    if(xPos + width >= x && x >= xPos &&  yPos + height >= y && y >= yPos){
        pressed = true;
        pressedCounter = 20;
    }
}

void Button::mouseTracking(int x, int y){
    inButton = false;
    if(xPos + width >= x && x >= xPos &&  yPos + height >= y && y >= yPos) inButton = true;
}

void Button::render(){
    ofSetColor(256, 0, 0);
    if(buttonText != "") ofDrawBitmapString(buttonText, xPos+width/2, yPos+height/2);
    else{
        ofSetColor(169,169,169);
        inButton && pressedCounter == -1 ?  buttonImage.draw(growX,growY,growW,growH) : buttonImage.draw(xPos,yPos,width,height);
    }
}

bool Button::wasPressed(){
    return pressed;
}

bool Button::isInButton(){
    return inButton;
}

int Button::getX(){
    return xPos;
}
void Button::setX(int x){
    xPos = x;
    growX = xPos - (width*growFactor)/2;
}
int Button::getY(){
    return yPos;
}
void Button::setY(int y){
    yPos = y;
    growY = yPos - (height*growFactor)/2;
}
int Button::getWidth(){
    return width;
}
int Button::getHeight(){
    return height;
}

