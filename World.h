#ifndef _WORLD_H
#define _WORLD_H

#include <array>
#include "Organism.h"
using namespace std;

class Organism;//Superclass organism is an abstraction of an entity inside a world

const int ARRAYSIZE = 20;//Default grid dimensions
const int MAXROW = ARRAYSIZE;
const int MAXCOL = ARRAYSIZE;
const int INITHUMANS = 100;//Initial population of humans
const int INITZOMBIES = 5;//Initial population of zombies
const int SPAWNHUMANS = 3;//A step in time when humans spawn
const int SPAWNZOMBIES = 8;//A step in time when zombies spawn
const int STARVEZOMBIE = 3;//A step in time when zombies starve

class World//Prototype of a world object
{
private:
    Organism *grid[MAXROW][MAXCOL];//Dynamic 2D array where objects are contained in memory

    //Private member methods
    void populateWorld();
    void nullifyWorld();
    void setMovedToFalse();
    void moveOrganisms();
    void spawnOrganisms();

public:
    //Constructor(s), Destructor(s)
    //World(int rand);
    World();
    virtual ~World();

    //Public member methods (For interface/driver)
    Organism *getOrganism(int x, int y) const;
    void setOrganism(int x,int y, Organism* thisOrganism);
    void display() const;
    void displayForunix() const;
    void displayForWindows() const;
    void gameCycle();
    int returnRandom(int thisNumber) const;

    int count = 0;
    int numOfHumans = INITHUMANS;
    int numOfZombies = INITZOMBIES;

    void countOrganisms();

    string H = "\033[1;32mO\033[0m";
    string Z = "\033[1;31mZ\033[0m";
    string H2 = "\033[1;32m██\033[0m";
    string Z2 = "\033[1;31m██\033[0m";
    string EMPTY = "\033[1;30m██\033[0m";

    void convertZombies();

    bool checkExtinction();

    void starveZombies();
};

#endif //ZOMBIESVSHUMANS_WORLD_H
