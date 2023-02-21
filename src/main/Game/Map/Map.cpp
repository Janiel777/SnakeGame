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

    matrixCopy = new vector<vector<int>>(*matrix);

    
    fruitSpawner = new FruitSpawner(em, x, y, w, h, squaresLength, matrix);
    em->snake = new Snake(x + int(w/2) * squaresLength, y + int(h/2) * squaresLength, squaresLength, squaresLength);
    
}

void Map::tick(){

    if(ofGetWidth() != windowW || ofGetHeight() != windowH) updateEntitiesCoordinates();
    if(em->snake->remove)em->spawNewSnake(x,y,w,h,squaresLength);
    //calculacion de la ruta
    //cambiamos la cola a 0 (lugar vacio en la matrix)
    //luego se mueve la culebra
    //setiamos la culebra en la matrix

    if(!searching){
        (*matrix)[(em->snake->body[em->snake->body.size()-1]->getY() - y) / squaresLength][(em->snake->body[em->snake->body.size()-1]->getX() - x) / squaresLength] = 0;
        em->tick();

        setSnakeInMatrix();
        setFruitInMatrix();
        fruitSpawner->tick();
    }

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

    if(searching) BFStraversal();
}

void Map::render(){
    em->render();
    
    if(searching) drawPaths();
    // drawGrid();
    if(showHud) drawHud();
    
}

void Map::BFStraversal(){

    //paths es una lista de listas de int - list< list<int> >
    //en donde las listas que guardan integers van a guardar el 
    //row en el front de la lista y el column en el back de la lista.
    //van a ser solamente listas de 2 integers todas. Son para
    //guardar los pares de coordenadas de la matrix.
    if(paths.empty()){
        int row = (em->snake->getY() - y) / squaresLength;
        int column = (em->snake->getX() - x) / squaresLength;

        if((*matrixCopy)[row+1][column] == 0){
            paths.push_back(list<int>({row+1,column}));
            (*matrixCopy)[row+1][column] = -1;
        }
        if((*matrixCopy)[row-1][column] == 0){
            paths.push_back(list<int>({row-1,column}));
            (*matrixCopy)[row-1][column] = -1;
        }
        if((*matrixCopy)[row][column+1] == 0){
            paths.push_back(list<int>({row,column+1}));
            (*matrixCopy)[row][column+1] = -1;
        }
        if((*matrixCopy)[row][column-1] == 0){
            paths.push_back(list<int>({row,column-1}));
            (*matrixCopy)[row][column-1] = -1;
        }

        (*matrixCopy)[row][column] = -1;

    }else{

        int row = paths.front().front();
        int column = paths.front().back();

        if((*matrixCopy)[row+1][column] == 0){
            paths.push_back(list<int>({row+1,column}));
            (*matrixCopy)[row+1][column] = -1;
        }
        if((*matrixCopy)[row-1][column] == 0){
            paths.push_back(list<int>({row-1,column}));
            (*matrixCopy)[row-1][column] = -1;
        }
        if((*matrixCopy)[row][column+1] == 0){
            paths.push_back(list<int>({row,column+1}));
            (*matrixCopy)[row][column+1] = -1;
        }
        if((*matrixCopy)[row][column-1] == 0){
            paths.push_back(list<int>({row,column-1}));
            (*matrixCopy)[row][column-1] = -1;
        }

        paths.pop_front();
    }

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
    if(key == '1'){
        searching = !searching;
        em->snake->setStopMoving(!em->snake->getStopMoving());
        paths.clear();
        matrixCopy->clear();
        matrixCopy->insert(matrixCopy->begin(), matrix->begin(), matrix->end());
    } 
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

void Map::drawPaths(){
    list<list<int>>::iterator it;
    for (it = paths.begin(); it != paths.end(); ++it){
        ofSetColor(0,0,0);
        ofDrawRectangle(x + (*it).back() * squaresLength, y + (*it).front() * squaresLength, squaresLength, squaresLength);
    }   
    // ofDrawBitmapString(ofToString(paths.size()), 20,100);
    // ofDrawBitmapString(ofToString(paths.back().front()) + " " +  ofToString(paths.back().back()), 20,120);
}

void Map::drawMatrix(vector<vector<int>>* m){
    ofSetColor(0,0,0);
    for(int row = 0; row < (*m).size(); row++){
        for(int column = 0; column < (*m)[row].size(); column++){
            ofDrawBitmapString(ofToString((*m)[row][column]), x + column * squaresLength, y + row * squaresLength + squaresLength);
        }
    }
    ofDrawBitmapString(ofToString((*m).size()), 20,20);
}


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
    //searching ? drawMatrix(matrixCopy) : drawMatrix(matrix);
}

void Map::setFruitInMatrix(){
    for(Fruit* f: em->fruits){
        (*matrix)[(f->getY() - y) / squaresLength][(f->getX() - x) / squaresLength] = 2;
    }
}

void Map::setSnakeInMatrix(){
    if((*matrix)[(em->snake->body[0]->getY() - y) / squaresLength][(em->snake->body[0]->getX() - x) / squaresLength] != 1){
        (*matrix)[(em->snake->body[0]->getY() - y) / squaresLength][(em->snake->body[0]->getX() - x) / squaresLength] = 3;
    }
    for(int i = 1; i < em->snake->body.size(); i++){
        (*matrix)[(em->snake->body[i]->getY() - y) / squaresLength][(em->snake->body[i]->getX() - x) / squaresLength] = 3;
    }
}

/**
 * Here the buttons and their
 * respective texts are drawn
 * 
 */



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