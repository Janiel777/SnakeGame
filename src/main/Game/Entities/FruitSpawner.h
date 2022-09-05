#pragma once
#include "ofMain.h"
#include "EntityManager.h"

class FruitSpawner{
private:
    EntityManager* em;
    vector<vector<int>>* matrix;
    int mapX;
    int mapY;
    int squareLength;
    int mapW;
    int mapH;
    int numOfFruits = 20;
public:
    FruitSpawner(EntityManager* em, int mapX, int mapY, int mapW, int mapH, int squareLength, vector<vector<int>>* matrix);
    void tick();
    void spawnFruit();
    void setMapX(int num) {mapX = num;}
    void setMapY(int num) {mapY = num;}
    void setMapW(int num) {mapW = num;}
    void setMapH(int num) {mapH = num;}
    int getNumOfFruits(){return numOfFruits;}
    void setNumOfFruits(int num) {numOfFruits = num;}
    ~FruitSpawner();
};


