#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    input = ' ';
    score = 0;
}

/*GameMechs::~GameMechs()
{
    //currently no heap members. included incase there may be some in the future
}*/

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    input = ' ';
    score = 0;
}
// do you need a destructor?



bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;

}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;

}
    

char GameMechs::getInput() const
{
    return input;

}

int GameMechs::getScore() const
{
    return score;

}

void GameMechs::incrementScore()
{
    score++;
    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;

}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;

}


void GameMechs::setExitTrue()
{

    exitFlag = true;

}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
    
}

void GameMechs::setInput(char this_input)
{
    input = this_input;

}

void GameMechs::clearInput()
{
    input = ' ';

}



//generate food pos as random tile within board

void GameMechs::incrementScoreBy(int x)
{
    score+=x;
}
