#ifndef _Human_H
#define _Human_H
#include "Organism.h"
#include "World.h"
#include <vector>


class Human : public Organism//Prototype for zombie object : extends organism
{

private:
    World *world;

public:
    //Constructor(s), Destructor(s)
    Human();
    Human(World *world, int xPos, int yPos);
    virtual ~Human();

    //Member methods
    virtual speciesType getSpecies();
    virtual void move();
    virtual void spawn();
};
#endif //ZOMBIESVSHUMANS_HUMAN_H
