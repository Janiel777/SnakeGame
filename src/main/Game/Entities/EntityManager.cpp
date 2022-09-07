#include "EntityManager.h"


void EntityManager::tick(){
    snake->tick();
    checkCollisions();

}

void EntityManager::render(){
    for(Bound* b : bounds) b->render();

    for(Fruit* f : fruits) f->render();

    snake->render();

}

void EntityManager::keyPressed(int key){
    snake->keyPressed(key);
}

/**
 * @brief This method removes the fruit from the parameter of the fruit vector
 * 
 * @param f The fruit to remove
 */
void EntityManager::deleteDruit(Fruit* f){
    fruits.erase(find(fruits.begin(), fruits.end(), f));
    delete f;
}

void EntityManager::spawNewSnake(int mapX, int mapY, int mapW, int mapH, int squaresLength){
    for(int i = 1; i < snake->body.size(); i++){
        // if((*matrix)[(snake->body[i]->getY() - mapY) / squaresLength][(snake->body[i]->getX() - mapX) / squaresLength] == 1) continue;
        (*matrix)[(snake->body[i]->getY() - mapY) / squaresLength][(snake->body[i]->getX() - mapX) / squaresLength] = 0;
    }
    delete snake;
    snake = new Snake(mapX + int(mapW/2) * squaresLength, mapY + int(mapH/2) * squaresLength, squaresLength, squaresLength);
}

/**
 * @brief 
 * 
 */
void EntityManager::deleteFruits(int mapX, int mapY, int mapW, int mapH, int squaresLength){
    vector<Fruit*>::iterator it = fruits.begin();
    while(it != fruits.end()){
        (*matrix)[((*it)->getY() - mapY) / squaresLength][((*it)->getX() - mapX) / squaresLength] = 0;
        fruits.erase(it);
        delete *it;
    } 
}

void EntityManager::deleteBounds(){
    vector<Bound*>::iterator it = bounds.begin();
    while(it != bounds.end()){
        bounds.erase(it);
        delete *it;
    } 
}

void EntityManager::checkCollisions(){
    for(Bound* b: bounds){
        if(snake->getBounds().intersects(b->getBounds())){
            snake->remove = true;
        }
    }

    for(Fruit* f: fruits){
        if(snake->getBounds().intersects(f->getBounds())){
            deleteDruit(f);
            snake->increaseSize();
            break;
        }
    }

    for(int i = 2; i < snake->body.size(); i++){
        if(snake->getBounds().intersects(*snake->body[i])){
            snake->remove = true;
        }
    }

    for(Fruit* f: fruits){
        for(Bound* b : bounds){
            if(f->getBounds().intersects(b->getBounds())){
                f->remove = true;
                break;
            }
            
        }
    }
}




EntityManager::~EntityManager(){
    for(Bound* b : bounds) delete b;

    for(Fruit* f : fruits) delete f;

    delete snake;
}