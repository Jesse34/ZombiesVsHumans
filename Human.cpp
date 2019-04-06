//
// Created by prog2100 on 26/11/17.
//

#include "Human.h"

#include <vector>
#include <iostream>
#include <random>

using namespace std;

Human::Human() {}

Human::Human(World *world, int x, int y) : Organism(world, xPos, yPos) {
    this->world = world;
    this->x = x;
    this->y = y;
}

Human::~Human() {}

///MOVE METHOD
void Human::move() {

    int oldX = x;
    int oldY = y;

    possibleMoves.clear();
    int left = y-1;
    int up = x-1;
    int right = y+1;
    int down = x+1;

    ////Check Left
    if(left >= 0) {
        if (world->getOrganism(x,left) == nullptr) {
            possibleMoves.push_back(moveList(LEFT));
        }
    }
    ////Check Up
    if(up >= 0) {
        if (world->getOrganism(up,y) == nullptr) {
            possibleMoves.push_back(moveList(UP));
        }
    }
    ////Check Right
    if(right < MAXCOL) {
        if (world->getOrganism(x,right) == nullptr) {
            possibleMoves.push_back(moveList(RIGHT));
        }
    }
    ////Check Down
    if(down < MAXROW) {
        if (world->getOrganism(down,y) == nullptr) {
            possibleMoves.push_back(moveList(DOWN));
        }
    }


/// Possible moves int values
/// { LEFT, UP, RIGHT, DOWN, UPRIGHT, DOWNRIGHT, UPLEFT, DOWNLEFT }


    if(!possibleMoves.empty()){
        int moveSelection = world->returnRandom(static_cast<int>(possibleMoves.size() - 1));

        switch(possibleMoves[moveSelection]){
            case 0:
                y = left;
                break;
            case 1:
                x = up;
                break;
            case 2:
                y = right;
                break;
            case 3:
                x = down;
                break;
            default:
                this->setSteps(0);
                break;
        }
        this->setPosition(x,y);

        world->setOrganism(this->x,this->y, this);
        world->setOrganism(oldX,oldY, nullptr);

        setMoved(true);
        setSteps(++stepsInTime);
    }
}
///END MOVE METHOD

speciesType Human::getSpecies() { return HUMAN; }


void Human::spawn() {

}
