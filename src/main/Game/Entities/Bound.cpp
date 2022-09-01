#include "Bound.h"

Bound::Bound(int x, int y, int w, int h) : Entity(x, y, w, h){
    
}

void Bound::render(){
    ofFill();
    ofSetColor(255,0,0);
    ofDrawRectangle(x,y,w,h);
}

void Bound::tick(){
    
}

Bound::~Bound(){
    
}