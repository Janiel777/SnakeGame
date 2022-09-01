#include "Fruit.h"

Fruit::Fruit(int x, int y, int w, int h) : Entity(x, y, w, h){
    
}

void Fruit::render(){
    ofFill();
    ofSetColor(255,255,0);
    ofDrawRectangle(x,y,w,h);
}

void Fruit::tick(){
    
}

Fruit::~Fruit(){
    
}