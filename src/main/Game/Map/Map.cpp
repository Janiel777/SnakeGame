#include "Map.h"

Map::Map(int w, int h, int squaresLength){
    this->w = w;
    this->h = h;
    this->squaresLength = squaresLength;
    em = new EntityManager();
    matrix = new vector<vector<int>>();
    em->matrix = matrix;

    plusSign.load("images/plusSign.png");
    minusSign.load("images/minusSign.png");
    font.load("Fonts/Minecraft.ttf", 14);

    int string1 = font.stringWidth("ap Width      Map Height      Nu");
    int string2 = font.stringWidth("ap Height      Nu");
    int string3 = font.stringWidth("Nu");
    int string4 = font.stringWidth("mber of Fruits      Sn");
    
    increasWidthButton = new Button(ofGetWidth()/2 - string1, 33, 20, 20, plusSign);
    decreaseWidthButton = new Button(ofGetWidth()/2 - string1 + 25, 33, 20,20, minusSign);
    increasHeightButton = new Button(ofGetWidth()/2 - string2, 33, 20,20, plusSign);
    decreaseHeightButton = new Button(ofGetWidth()/2 - string2 + 25, 33, 20,20, minusSign);
    increaseFuitsButton = new Button(ofGetWidth()/2 + string3, 33, 20,20, plusSign);
    decreaseFuitsButton = new Button(ofGetWidth()/2 + string3 + 25, 33, 20,20, minusSign);
    increasSnakeSpeedButton = new Button(ofGetWidth()/2 + string4, 33, 20,20, plusSign);
    decreaseSnakeSpeedButton = new Button(ofGetWidth()/2 + string4 + 25, 33, 20,20, minusSign);

    

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
        matrix->push_back(vector<int>());
        for(int j = 0; j < w; j++){
            (*matrix)[i].push_back(0);
            if(i == 0 || j == 0 || i == h-1 || j == w-1){
                (*matrix)[i][j] = 1;
                em->bounds.push_back(new Bound(x + squaresLength * j, y + squaresLength * i, squaresLength, squaresLength));
            }
        } 
    }

    
    fruitSpawner = new FruitSpawner(em, x, y, w, h, squaresLength, matrix);
    em->snake = new Snake(x + int(w/2) * squaresLength, y + int(h/2) * squaresLength, squaresLength, squaresLength);
    
}

void Map::tick(){
    if(ofGetWidth() != windowW || ofGetHeight() != windowH) updateEntitiesCoordinates();

    //calculacion de la ruta
    //cambiamos la cola a 0 (lugar vacio en la matrix)
    //luego se mueve la culebra
    //setiamos la culebra en la matrix
    (*matrix)[(em->snake->body[em->snake->body.size()-1]->getY() - y) / squaresLength][(em->snake->body[em->snake->body.size()-1]->getX() - x) / squaresLength] = 0;
    em->tick();
    setSnakeInMatrix();
    setFruitInMatrix();
    fruitSpawner->tick();
    
    
    if(em->snake->remove)em->spawNewSnake(x,y,w,h,squaresLength);

    if(showHud){
        increasWidthButton->tick();
        decreaseWidthButton->tick();
        increasHeightButton->tick();
        decreaseHeightButton->tick();
        increaseFuitsButton->tick();
        decreaseFuitsButton->tick();
        increasSnakeSpeedButton->tick();
        decreaseSnakeSpeedButton->tick();

        if(increasWidthButton->wasPressed() || decreaseWidthButton->wasPressed() || increasHeightButton->wasPressed() || decreaseHeightButton->wasPressed()){
            changeMapDimensions();
        } 
        if(increaseFuitsButton->wasPressed() && fruitSpawner->getNumOfFruits() <= 19){
            fruitSpawner->setNumOfFruits(fruitSpawner->getNumOfFruits()+1);
            em->deleteFruits(x,y,w,h,squaresLength);
            increaseFuitsButton->reset();
        } 
        if(decreaseFuitsButton->wasPressed() && fruitSpawner->getNumOfFruits() >=1){
            fruitSpawner->setNumOfFruits(fruitSpawner->getNumOfFruits()-1);
            em->deleteFruits(x,y,w,h,squaresLength);
            decreaseFuitsButton->reset();
        } 
        if(increasSnakeSpeedButton->wasPressed() && em->snake->getSpeed() >= 2){
            em->snake->setSpeed(em->snake->getSpeed() - 1);
            increasSnakeSpeedButton->reset();
        }
        if(decreaseSnakeSpeedButton->wasPressed() && em->snake->getSpeed() <= 20){
            em->snake->setSpeed(em->snake->getSpeed() + 1);
            decreaseSnakeSpeedButton->reset();
        }
    }

    
}

void Map::render(){
    em->render();
    drawGrid();
    if(showHud) drawHud();
    drawMatrix();
}

/**
 *  This method is called when one of the buttons that changes
 *  the size of the map is pressed. Mainly what it does is call
 *  the updateEntitiesCoordinates method so that everything is centralized again.
 */
void Map::changeMapDimensions(){

    em->deleteBounds();
    em->deleteFruits(x,y,w,h,squaresLength);

    if(increasWidthButton->wasPressed()) w++;
    if(decreaseWidthButton->wasPressed()) w--;
    if(increasHeightButton->wasPressed())h++;
    if(decreaseHeightButton->wasPressed()) h--;

    (*matrix).clear();
    for(int i = 0; i < h; i++){
        (*matrix).push_back(vector<int>());
        for(int j = 0; j < w; j++){
            (*matrix)[i].push_back(0);
            if(i == 0 || j == 0 || i == h-1 || j == w-1){
                (*matrix)[i][j] = 1;
                em->bounds.push_back(new Bound(x + squaresLength * j, y + squaresLength * i, squaresLength, squaresLength));
            }
        } 
    }

    updateEntitiesCoordinates();
    increasWidthButton->reset();
    decreaseWidthButton->reset();
    increasHeightButton->reset();
    decreaseHeightButton->reset();

    fruitSpawner->setMapX(x);
    fruitSpawner->setMapY(y);
    fruitSpawner->setMapW(w);
    fruitSpawner->setMapH(h);


}


void Map::keyPressed(int key){
    em->keyPressed(key);
    if(key == ' ') showHud = !showHud;
}

void Map::mousePressed(int x, int y, int button){
    if(showHud){
        increasWidthButton->mousePressed(x,y);
        decreaseWidthButton->mousePressed(x,y);
        increasHeightButton->mousePressed(x,y);
        decreaseHeightButton->mousePressed(x,y);
        increaseFuitsButton->mousePressed(x,y);
        decreaseFuitsButton->mousePressed(x,y);
        increasSnakeSpeedButton->mousePressed(x,y);
        decreaseSnakeSpeedButton->mousePressed(x,y);
    }
}
/**
 * @brief This method is used to know the position of the mouse.
 *  Specifically it is used to know when the mouse is over a 
 * button so that it grows a little and lets the user know intuitively
 *  that it can be pressed.
 * 
 * @param x Mouse x-coordinate
 * @param y Mouse y-coordinate
 */
void Map::mouseTracking(int x, int y){
    if(showHud){
        increasWidthButton->mouseTracking(x,y);
        decreaseWidthButton->mouseTracking(x,y);
        increasHeightButton->mouseTracking(x,y);
        decreaseHeightButton->mouseTracking(x,y);
        increaseFuitsButton->mouseTracking(x,y);
        decreaseFuitsButton->mouseTracking(x,y);
        increasSnakeSpeedButton->mouseTracking(x,y);
        decreaseSnakeSpeedButton->mouseTracking(x,y);
    }
    
}

void Map::reset(){
    
}
/**
 * Here the grid lines are drawn.
 * 
 */
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

void Map::drawMatrix(){
    ofSetColor(0,0,0);
    for(int row = 0; row < (*matrix).size(); row++){
        for(int column = 0; column < (*matrix)[row].size(); column++){
            ofDrawBitmapString(ofToString((*matrix)[row][column]), x + column * squaresLength, y + row * squaresLength + squaresLength);
        }
    }
    ofDrawBitmapString(ofToString((*matrix).size()), 20,20);
}

void Map::setFruitInMatrix(){
    for(Fruit* f: em->fruits){
        (*matrix)[(f->getY() - y) / squaresLength][(f->getX() - x) / squaresLength] = 2;
    }
}

void Map::setSnakeInMatrix(){
    for(ofRectangle* r: em->snake->body){
        if((*matrix)[(r->getY() - y) / squaresLength][(r->getX() - x) / squaresLength] == 1) continue;
        (*matrix)[(r->getY() - y) / squaresLength][(r->getX() - x) / squaresLength] = 3;
    }
}

/**
 * Here the buttons and their
 * respective texts are drawn
 * 
 */
void Map::drawHud(){
    ofSetColor(255,255,255);
    int stringWidth = font.stringWidth("Map Width      Map Height      Number of Fruits      Snake Speed");
    font.drawString("Map Width      Map Height      Number of Fruits      Snake Speed", ofGetWidth()/2 - stringWidth/2, 20);
    if(showHud){
        increasWidthButton->render();
        decreaseWidthButton->render();
        increasHeightButton->render();
        decreaseHeightButton->render();
        increaseFuitsButton->render();
        decreaseFuitsButton->render();
        increasSnakeSpeedButton->render();
        decreaseSnakeSpeedButton->render();
    }
}


/**
 * This method calculates the new coordinates
 * by changing the size of the openFramesWorks window. 
 * Change the coordinates of: 
 * all bounds, 
 * all the fruits, 
 * the snake and its body,
 * and all the buttons.
 */
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

    em->snake->updateCoordinates(oldX,oldY,x,y);
    fruitSpawner->setMapX(x);
    fruitSpawner->setMapY(y);
    fruitSpawner->setMapW(w);
    fruitSpawner->setMapH(h);

    int string1 = font.stringWidth("ap Width      Map Height      Nu");
    int string2 = font.stringWidth("ap Height      Nu");
    int string3 = font.stringWidth("Nu");
    int string4 = font.stringWidth("mber of Fruits      Sn");
    increasWidthButton->setX(ofGetWidth()/2 - string1);
    decreaseWidthButton->setX(ofGetWidth()/2 - string1 + 25);
    increasHeightButton->setX(ofGetWidth()/2 - string2);
    decreaseHeightButton->setX(ofGetWidth()/2 - string2 + 25);
    increaseFuitsButton->setX(ofGetWidth()/2 + string3);
    decreaseFuitsButton->setX(ofGetWidth()/2 + string3 + 25);
    increasSnakeSpeedButton->setX(ofGetWidth()/2 + string4);
    decreaseSnakeSpeedButton->setX(ofGetWidth()/2 + string4 + 25);

    windowW = ofGetWidth();
    windowH = ofGetHeight();
}

Map::~Map(){
    delete em;
    delete fruitSpawner;
}