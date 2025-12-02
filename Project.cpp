#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gm;
Player* player;
Food* food;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gm->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();

    srand((unsigned)time(NULL));

    gm = new GameMechs();
    food = new Food();
    player = new Player(gm,food);

    //generating snake
    objPosArrayList* snakeList = player->getPlayerPos();

    //generating foods
    // objPosArrayList* foodBucket = food->getFoodBucket();
    
    // Generate snake length
    // objPos snakeHead = snakeList->getHeadElement();

    // for(int i = 1; i <= 4; i++)
    // {
    //     objPos newSegment(snakeHead.pos->x - i, snakeHead.pos->y, '*');
    //     snakeList->insertTail(newSegment);
    // }

    food->generateFoods(snakeList, gm->getBoardSizeX(), gm->getBoardSizeY());
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char input = MacUILib_getChar();   
        gm->setInput(input);
     }
   
}

void RunLogic(void)
{
    char in = gm->getInput();

    if(in != 0){
        if(in == 27) // esc key
        {
            MacUILib_printf("You exited the game! Final Score: %d\n", gm->getScore());
            gm->setExitTrue();
        }

        else
        {
            player->updatePlayerDir();
        }
    }
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    objPosArrayList* snake = player->getPlayerPos();
    // objPos foodPos = food->getFoodPos();
    objPosArrayList* bucket = food->getFoodBucket();


    MacUILib_printf("      WELCOME TO SNAKE!       \n");
    for (int i = 0; i < gm->getBoardSizeY(); i++)
    {
        for (int j = 0; j < gm->getBoardSizeX(); j++)
        {
            // Draw borders
            if (i == 0 || j == 0 || i == gm->getBoardSizeY() - 1 || j == gm->getBoardSizeX() - 1)
            { 
                MacUILib_printf("#");
            }
            else
            {
                bool isBodyPart = false, isFood = false;
                
                // Check if snake body part is at this position
                for(int k = 0; k < snake->getSize(); k++) //recursive call
                {
                    objPos bodyPart = snake->getElement(k);
                    if (j == bodyPart.pos->x && i == bodyPart.pos->y)
                    {
                        MacUILib_printf("%c", bodyPart.getSymbol());
                        isBodyPart = true;
                        break;
                    }
                }

                for(int k = 0; k < bucket->getSize(); k++)
                {
                    objPos food = bucket->getElement(k);
                    if (j == food.pos->x && i == food.pos->y)
                    {
                        MacUILib_printf("%c", food.getSymbol());
                        isFood = true;
                        break;
                    }
                }

                // Draw empty space
                if(!isBodyPart && !isFood)
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("use WASD to move the snake. Press ESC to exit.\n");
    MacUILib_printf("Score: %d\n", gm->getScore());

    if(gm->getLoseFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("Game Over! You ran into yourself! Final Score: %d\n", gm->getScore());
        gm->setExitTrue();
        return;
    }

    if(gm->getExitFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("You exited the game! Final Score: %d\n", gm->getScore());
    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

    delete player;
    player = nullptr;

    delete gm;
    gm = nullptr;

    delete food;
    food = nullptr;

    MacUILib_uninit();
}
