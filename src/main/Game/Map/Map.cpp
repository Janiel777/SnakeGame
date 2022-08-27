#include "Map.h"

Map::Map(int w, int h, int squaresLength){
    this->w = w;
    this->h = h;
    this->squaresLength = squaresLength;


    if(w % 2 == 0){
        x = ofGetWidth()/2 - w/2*squaresLength;//The squeare are 10 * 10 pixels
    }else{
        x = ofGetWidth()/2 - int(w/2)*squaresLength - squaresLength/2;
    }

    if(y % 2 == 0){
        y = ofGetHeight()/2 - h/2*squaresLength;
    }else{
        y = ofGetHeight()/2 - int(y/2)*squaresLength - squaresLength/2;
    }

    for(int i = 0; i < h; i++){
        matrix.push_back(vector<int>());
        for(int j = 0; j < w; j++){
            matrix[i].push_back(0);
            if(i == 0 || j == 0 || i == h-1 || j == w-1){
                matrix[i][j] = 1;
                bounds.push_back(new Bound(x + squaresLength * j, y + squaresLength * i, squaresLength, squaresLength));
            }
        } 
    }
    
}

void Map::render(){

    for(Entity* b : bounds){
        b->render();
    }


    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(0,0,0);
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            ofDrawRectangle(x + i * squaresLength, y + j * squaresLength, squaresLength, squaresLength);
        }
    }

    
}

void Map::tick(){
    if(ofGetWidth() != windowW || ofGetHeight() != windowH){

        int oldX = x;
        int oldY = y;
        
        if(w % 2 == 0){
            x = ofGetWidth()/2 - w/2*squaresLength;
        }else{
            x = ofGetWidth()/2 - int(w/2)*squaresLength - squaresLength/2;
        }

        if(y % 2 == 0){
            y = ofGetHeight()/2 - h/2*squaresLength;
        }else{
            y = ofGetHeight()/2 - int(y/2)*squaresLength - squaresLength/2;
        }

        for(Entity* b : bounds){
            bool founded = false;

            for(int i = 0; i < h; i++){
                for(int j = 0; j < w; j++){
                    if(i == 0 || j == 0 || i == h-1 || j == w-1){
                        if(b->getX() == oldX + squaresLength * j && b->getY() == oldY + squaresLength * i){
                            b->setX(x + squaresLength * j);
                            b->setY(y + squaresLength * i);
                            founded = true;
                        }
                    }
                    if(founded) break;
                } 
                if(founded) break;
            }
            
        }


        windowW = ofGetWidth();
        windowH = ofGetHeight();
    }

    
}