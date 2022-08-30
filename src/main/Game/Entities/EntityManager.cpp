#include "EntityManager.h"


void EntityManager::tick(){
    

    for(Bound* b : bounds){
        b->tick();
    }

    vector<int> toRemove;

    for(int i = 0; i < fruits.size(); i++){
        if(!fruits[i]->remove){
            fruits[i]->tick();
        }else{
            toRemove.push_back(i);
        }
    }

    for(unsigned int removable: toRemove){
        Entity* entityPointer = *(fruits.begin() + removable);
        fruits.erase(fruits.begin() + removable);
        delete entityPointer;
    }

    toRemove.clear();

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

void EntityManager::checkCollisions(){
    for(Bound* b: bounds){
        if(snake->getBounds().intersects(b->getBounds())){
            snake->remove = true;
        }
    }

    for(Fruit* f: fruits){
        if(snake->getBounds().intersects(f->getBounds())){
            f->remove = true;
            snake->increaseSize();
        }
    }

    for(int i = 2; i < snake->body.size(); i++){
        if(snake->getBounds().intersects(snake->body[i])){
            snake->remove = true;
        }
    }
}




EntityManager::~EntityManager(){
    for(Bound* b : bounds) delete b;

    for(Fruit* f : fruits) delete f;

    delete snake;
}