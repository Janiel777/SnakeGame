#include "Map.h"

Map::Map(int w, int h, int squaresLength){
    this->w = w;
    this->h = h;
    this->squaresLength = squaresLength;
    em = new EntityManager();
    

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

    for(int i = 0; i < h; i++){
        matrix.push_back(vector<int>());
        for(int j = 0; j < w; j++){
            matrix[i].push_back(0);
            if(i == 0 || j == 0 || i == h-1 || j == w-1){
                matrix[i][j] = 1;
                em->bounds.push_back(new Bound(x + squaresLength * j, y + squaresLength * i, squaresLength, squaresLength));
            }
        } 
    }

    
    fruitSpawner = new FruitSpawner(em, x, y, w, h, squaresLength);
    em->snake = new Snake(x + int(w/2) * squaresLength, y + int(h/2) * squaresLength, squaresLength, squaresLength);
    
}

void Map::tick(){
    if(ofGetWidth() != windowW || ofGetHeight() != windowH) updateEntitiesCoordinates();
    
    em->tick();
    if(em->snake->remove){
        delete em->snake;
        em->snake = new Snake(x + int(w/2) * squaresLength, y + int(h/2) * squaresLength, squaresLength, squaresLength);
    } 
    fruitSpawner->tick();
    
}

void Map::render(){

    em->render();
    drawGrid();

}



void Map::keyPressed(int key){
    em->keyPressed(key);
}

void Map::drawGrid(){
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(0,0,0);
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            ofDrawRectangle(x + i * squaresLength, y + j * squaresLength, squaresLength, squaresLength);
        }
    }
}

void Map::updateEntitiesCoordinates(){
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

    for(Bound* e : em->bounds){
        bool founded = false;

        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                    if(e->getX() == oldX + squaresLength * j && e->getY() == oldY + squaresLength * i){
                        e->setX(x + squaresLength * j);
                        e->setY(y + squaresLength * i);
                        founded = true;
                    }
                if(founded) break;
            } 
            if(founded) break;
        }
    }

    for(Fruit* f : em->fruits){
        bool founded = false;

        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                    if(f->getX() == oldX + squaresLength * j && f->getY() == oldY + squaresLength * i){
                        f->setX(x + squaresLength * j);
                        f->setY(y + squaresLength * i);
                    }   
                    if(founded) break;       
            }
            if(founded) break;
        }
            
    }


    windowW = ofGetWidth();
    windowH = ofGetHeight();
}

Map::~Map(){
    delete em;
    delete fruitSpawner;
}