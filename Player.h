#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();
        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();
        //after getting position, return to caller as an objPosArrayList reference
                
        bool checkFoodConsumption(const objPos &foodPos) const;
        void increasePlayerLength();
        bool checkSelfCollision() const;       



    private:
        enum Dir myDir;
        objPosArrayList* playerPosList; // composition with objPosArrayList class
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* foodRef;
};

#endif