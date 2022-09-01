#include "FruitSpawner.h"

FruitSpawner::FruitSpawner(EntityManager* em, int mapX, int mapY, int mapW, int mapH, int squareLength){
    this->em = em;
    this->mapX = mapX;
    this->mapY = mapY;
    this->mapW = mapW;
    this->mapH = mapH;
    this->squareLength = squareLength;
}

void FruitSpawner::tick(){
    if(em->fruits.size() < numOfFruits){
        spawnFruit();
    }
}

void FruitSpawner::spawnFruit(){
    em->fruits.push_back(new Fruit(mapX + int(ofRandom(1,mapW-1))*squareLength, mapY + int(ofRandom(1,mapH-1))*squareLength, squareLength, squareLength));
}

FruitSpawner::~FruitSpawner(){
    delete em;
}
