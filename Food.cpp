#include "Food.h"
#include <stdlib.h>
#include <time.h>

Food::Food()
{
    foodPos.setObjPos(objPos(0,0,'O')); 

    foodBucket = new objPosArrayList();
}

void Food::generateFood(objPosArrayList* snakeList, int boardSizeX,int boardSizeY)
{
    int randX,randY;
    bool valid = false;

    while (!valid)
    {
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;

        valid = true;

        for (int i = 0; i < snakeList->getSize(); i++)
        {
            //check if new food position overlaps with snake body (if it does regenerate)
            objPos body = snakeList->getElement(i);
            if (body.pos->x == randX && body.pos->y == randY)
            {
                valid = false;
                break;
            }
        }
    }

    //ensure that food does not spawn on player
    foodPos.setObjPos(objPos(randX,randY,'O'));
}

void Food::generateFoods(objPosArrayList* snakeList, int boardSizeX, int boardSizeY)
{
    foodBucket->clear();
//generate multiple food items
    for (int i = 0; i < 5; i++)
    {
        int randX,randY;
        bool valid = false;

        while (!valid)
        {
            //random seeding logic
            randX = rand() % (boardSizeX - 2) + 1;
            randY = rand() % (boardSizeY - 2) + 1;
    
            valid = true;
            //check if new food position overlaps with snake body
            for (int j = 0; j < snakeList->getSize(); j++)
            {
                objPos body = snakeList->getElement(j);
                if (body.pos->x == randX && body.pos->y == randY)
                {
                    valid = false;
                    break;
                }
            }
            //check if new food position overlaps with existing food positions
            for (int j = 0; j < foodBucket->getSize(); j++)
            {
                objPos food = foodBucket->getElement(j);
                if (food.pos->x == randX && food.pos->y == randY)
                {
                    valid = false;
                    break;
                }
            }
        }
        
        char symbol;

        if (i<2)
        {
            symbol = '@';
        }
        else
        {
            symbol = 'O';
        }
        objPos newFood(randX,randY,symbol);
        
        foodBucket->insertTail(newFood);
    }

}

objPos Food::getFoodPos() const
{
    return foodPos;
}

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

Food::~Food()
{
    delete foodBucket;
    foodBucket = nullptr;
}
