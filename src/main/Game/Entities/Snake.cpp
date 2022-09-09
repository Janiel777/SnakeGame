#include "Snake.h"

Snake::Snake(int x, int y, int w, int h) : Entity(x, y, w, h){
    body.push_back(new ofRectangle(x,y,w,h));
}

void Snake::render(){
    ofSetColor(255,255,0);
    for(ofRectangle* r: body){
        ofDrawRectangle(r->getX(), r->getY(), r->getWidth(), r->getHeight());
    }

}

void Snake::tick(){
    if(!stopMoving) counter++;
    if(counter == speed){

        for(int i = body.size()-1; i > 0; i--){
            body[i]->setX(body[i-1]->getX());
            body[i]->setY(body[i-1]->getY());
        }

        if(moving == UP) y -= h;
        if(moving == DOWN) y += h;
        if(moving == LEFT) x -= w;
        if(moving == RIGHT) x += w;
        counter = 0;
        body[0]->setX(x);
        body[0]->setY(y);
    }

}

void Snake::increaseSize(){
    ofRectangle* tail = body[body.size()-1];
    body.push_back(new ofRectangle(tail->x, tail->y, tail->width, tail->height));
}

void Snake::keyPressed(int key){
    if(key == 'w' && moving != DOWN) moving = UP;
    if(key == 's' && moving != UP) moving = DOWN;
    if(key == 'a' && moving != RIGHT) moving = LEFT;
    if(key == 'd' && moving != LEFT) moving = RIGHT;
}


void Snake::updateCoordinates(int oldMapX, int oldMapY, int mapX, int mapY){
    for(int i = 0; i < body.size(); i++){
        body[i]->setX(mapX + body[i]->getX() - oldMapX);
        body[i]->setY(mapY + body[i]->getY() - oldMapY);
        x = 0;
    }
    x = body[0]->getX();
    y = body[0]->getY();
    
}



Snake::~Snake(){

}