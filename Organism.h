#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <vector>
#include "World.h"

using namespace std;

enum speciesType {ZOMBIE, HUMAN};//List of species

class World;//World prototype

class Organism//Class world is a prototype of the world where gameplay executes
{
protected:
    //Member properties
    World *world;//An organism exists in this world
    enum moveList { LEFT, UP, RIGHT, DOWN, UPLEFT, UPRIGHT, DOWNRIGHT,  DOWNLEFT };//List of adjacent moves
    vector<int> possibleMoves;
    int x, y, xPos, yPos, stepsInTime;
    bool moved, hasSpawned;

public:
    //Constructor(s), Destructor(s)
    Organism();
    Organism(World *world, int x, int y);
    virtual ~Organism();

    //Absolute virtual methods
    virtual speciesType getSpecies() = 0;
    virtual void move() = 0;
    virtual void spawn() = 0;

    //Member methods
    bool getMoved() const;
    void setMoved(bool oneStep);

    bool getHasSpawned();
    void setHasSpawned(bool hasSpawned);

    int getSteps();
    void setSteps(int aStepinTime);

    void setPosition(int x, int y);
};
#endif //ZOMBIESVSHUMANS_ORGANISM_H
