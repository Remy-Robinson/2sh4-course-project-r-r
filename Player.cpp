#include "Player.h"
#include "MACUILib.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    // more actions to be included
    int player_x = mainGameMechsRef->getBoardSizeX()/2;
    int player_y = mainGameMechsRef->getBoardSizeY()/2;

    objPos headPos; 
    headPos.setObjPos(player_x,player_y,'*');
    playerPosList->insertHead(headPos);
}


objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList; //in order to return the whole snakebody
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    switch(input)
    {            
        //main key processing block
        case 'w': case 'W':
            if (myDir != DOWN) 
            {
                myDir = UP;
            }
            break;
                
        case 's': case 'S':
            if (myDir != UP) 
            {
                myDir = DOWN;
            }
            break;

        case 'a': case 'A':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
            
        case 'd': case 'D':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;        
    }

    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos headPos = playerPosList->getHeadElement();
    int x = headPos.pos->x;
    int y = headPos.pos->y;

    switch (myDir)
    {
        //FSM movement logic
        case STOP: //end movePlayer function early if no movement is detected
            return;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;

    }
    //after movement create newHead position

    int borderX = mainGameMechsRef->getBoardSizeX();
    int borderY = mainGameMechsRef->getBoardSizeY();

    //border control logic same as PPA**

    if (x == borderX-1) {
        x = 1;
    }
    if (x == 0) {
        x = borderX-2;
    }
    if (y == borderY-1) {
        y = 1;
    }
    if (y == 0) {
        y = borderY-2;
    }

    objPos newHead(x,y,headPos.getSymbol());
    playerPosList->insertHead(newHead);


    if(checkSelfCollision()) //if the player collides with itself
    {
        mainGameMechsRef->setLoseFlag();
        return;
    }

    objPosArrayList* bucket = foodRef->getFoodBucket();
    bool eaten = false;
    
    for (int i = 0; i < bucket->getSize(); i++)
    {
        
        objPos foodPos = bucket->getElement(i);

        if(checkFoodConsumption(foodPos)) //checks if head position matches the food position to register consumption
        {
            eaten = true;
            if (foodPos.getSymbol() == '@')
            {
                mainGameMechsRef->incrementScoreBy(10);
                playerPosList->removeTail(); //Do not grow (do normal routine)
            }
            else
            {
                mainGameMechsRef->incrementScore();
            }
            foodRef->generateFoods(playerPosList,borderX, borderY);
            break;
        }
    }
    if (!eaten)
    {
        playerPosList->removeTail(); //normal movement routine (no growth)
    }
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;
}


bool Player::checkFoodConsumption(const objPos &foodPos) const
//checks if the player's head position matches the food position
{
    objPos head = playerPosList->getHeadElement();

    return (head.pos->x == foodPos.pos->x && head.pos->y == foodPos.pos->y);
}

bool Player::checkSelfCollision() const
{
    objPos head = playerPosList->getHeadElement();

    // Check if the snake's head collides with any other part of its body
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos body = playerPosList->getElement(i);

        if (head.pos->x == body.pos->x && head.pos->y == body.pos->y)
        {
            return true;
        }
    }

    return false;
}
