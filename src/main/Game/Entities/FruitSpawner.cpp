#include "FruitSpawner.h"

FruitSpawner::FruitSpawner(EntityManager* em, int mapX, int mapY, int mapW, int mapH, int squareLength, vector<vector<int>>* matrix){
    this->em = em;
    this->mapX = mapX;
    this->mapY = mapY;
    this->mapW = mapW;
    this->mapH = mapH;
    this->squareLength = squareLength;
    this->matrix = matrix;
}

void FruitSpawner::tick(){
    if(em->fruits.size() < numOfFruits){
        spawnFruit();
    }
}

void FruitSpawner::spawnFruit(){
    int x = mapX + int(ofRandom(1,mapW-1))*squareLength;
    int y = mapY + int(ofRandom(1,mapH-1))*squareLength;
    // do
    // {
    //     x = mapX + int(ofRandom(1,mapW-1))*squareLength;
    //     y = mapY + int(ofRandom(1,mapH-1))*squareLength;
    // } while ((*matrix)[x][y] != 0);
    
    em->fruits.push_back(new Fruit(x, y, squareLength, squareLength));
}

FruitSpawner::~FruitSpawner(){
    delete em;
}
