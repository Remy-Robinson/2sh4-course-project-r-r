#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;
        objPosArrayList* foodBucket;

    public:
        Food();
        ~Food();
        
        void generateFood(objPosArrayList* snakeList,int boardSizeX, int boardSizeY);
        void generateFoods(objPosArrayList* snakeList, int boardSizeX, int boardSizeY);
        
        objPos getFoodPos() const;
        objPosArrayList* getFoodBucket() const;
        
};

#endif