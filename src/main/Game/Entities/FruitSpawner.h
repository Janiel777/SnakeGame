#pragma once
#include "ofMain.h"
#include "EntityManager.h"

class FruitSpawner{
private:
    EntityManager* em;
    int mapX;
    int mapY;
    int squareLength;
    int mapW;
    int mapH;
public:
    FruitSpawner(EntityManager* em, int mapX, int mapY, int mapW, int mapH, int squareLength);
    void tick();
    void spawnFruit();
    ~FruitSpawner();
};


