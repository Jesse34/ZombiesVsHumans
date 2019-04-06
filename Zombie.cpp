//
// Created by prog2100 on 26/11/17.
//

#include <algorithm>
#include "Zombie.h"
#include "Human.h"

Zombie::Zombie() {}

Zombie::Zombie(World *world, int x, int y) : Organism(world, x, y) {
    this->world = world;
    this->x = x;
    this->y = y;
}

Zombie::~Zombie() {}

void Zombie::move() {

    int oldX = this->x;
    int oldY = this->y;

    possibleMoves.clear();
    possibleEats.clear();

    int left = y - 1;
    int up = x - 1;
    int right = y + 1;
    int down = x + 1;

    bool ateHuman = false;

    ////Check Left
    if (left >= 0 && !ateHuman) {
        if (world->getOrganism(x, left) == nullptr) {
            possibleMoves.push_back(moveList(LEFT));
        } else if (world->getOrganism(x, left)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(LEFT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(x, left, this);
//            this->setPosition(x,left);
//            ateHuman = true;
        }
    }
    ////Check Up
    if (up >= 0 && !ateHuman) {
        if (world->getOrganism(up, y) == nullptr) {
            possibleMoves.push_back(moveList(UP));
        } else if (world->getOrganism(up, y)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(UP));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(up, y, this);
//            this->setPosition(up, y);
//            ateHuman = true;
        }
    }
    ////Check Right
    if (right < MAXCOL && !ateHuman) {
        if (world->getOrganism(x, right) == nullptr) {
            possibleMoves.push_back(moveList(RIGHT));
        } else if (world->getOrganism(x, right)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(RIGHT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(x, right, this);
//            this->setPosition(x, right);
//            ateHuman = true;
        }
    }
    ////Check Down
    if (down < MAXROW && !ateHuman) {
        if (world->getOrganism(down, y) == nullptr) {
            possibleMoves.push_back(moveList(DOWN));
        } else if (world->getOrganism(down, y)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(DOWN));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(down, y, this);
//            this->setPosition(down, y);
//            ateHuman = true;
        }
    }
    ////Check NW
    if (left >= 0 && up >= 0 && !ateHuman) {
        if (world->getOrganism(up, left) == nullptr) {
            possibleMoves.push_back(moveList(UPLEFT));
        } else if (world->getOrganism(up, left)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(UPLEFT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(up, left, this);
//            this->setPosition(up, left);
//            ateHuman = true;
        }
    }
    ////Check NE
    if (up >= 0 && right < MAXCOL && !ateHuman) {
        if (world->getOrganism(up, right) == nullptr) {
            possibleMoves.push_back(moveList(UPRIGHT));
        } else if (world->getOrganism(up, right)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(UPRIGHT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(up, right, this);
//            this->setPosition(up, right);
//            ateHuman = true;
        }
    }
    ////Check SE
    if (right < MAXCOL && down < MAXROW && !ateHuman) {
        if (world->getOrganism(down, right) == nullptr) {
            possibleMoves.push_back(moveList(DOWNRIGHT));
        } else if (world->getOrganism(down, right)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(DOWNRIGHT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(down, right, this);
//            this->setPosition(down, right);
//            ateHuman = true;
        }
    }
    ////Check SW
    if (down < MAXROW && left >= 0 && !ateHuman) {
        if (world->getOrganism(down, left) == nullptr) {
            possibleMoves.push_back(moveList(DOWNLEFT));
        } else if (world->getOrganism(down, left)->getSpecies() == HUMAN) {
            possibleEats.push_back(moveList(DOWNLEFT));

//            world->setOrganism(oldX,oldY, nullptr);
//            world->setOrganism(down, left, this);
//            this->setPosition(down, left);
//            ateHuman = true;
        }
    }

    /// Possible eat moves int values
    /// { LEFT, UP, RIGHT, DOWN, UPRIGHT, DOWNRIGHT, UPLEFT, DOWNLEFT }

    if (!possibleEats.empty()) {
        int eatSelection = world->returnRandom(static_cast<int>(possibleEats.size() - 1));

        world->setOrganism(oldX,oldY, nullptr);

        switch (possibleEats[eatSelection]) {
            case 0:
                world->setOrganism(x, left, this);
                this->setPosition(x,left);
                break;
            case 1:
                world->setOrganism(up, y, this);
                this->setPosition(up, y);
                break;
            case 2:
                world->setOrganism(x, right, this);
                this->setPosition(x, right);
                break;
            case 3:
                world->setOrganism(down, y, this);
                this->setPosition(down, y);
                break;
            case 4:
                world->setOrganism(up, left, this);
                this->setPosition(up, left);
                break;
            case 5:
                world->setOrganism(up, right, this);
                this->setPosition(up, right);
                break;
            case 6:
                world->setOrganism(down, right, this);
                this->setPosition(down, right);
                break;
            case 7:
                world->setOrganism(down, left, this);
                this->setPosition(down, left);
                break;
            default:
                break;
        }
        ateHuman = true;
    }

    //If no Human was eaten, look for a place to move to
    if (!ateHuman){
        if (!possibleMoves.empty()) {
            int moveSelection = world->returnRandom(static_cast<int>(possibleMoves.size() - 1));

            switch (possibleMoves[moveSelection]) {
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
                case 4:
                    x = up;
                    y = left;
                    break;
                case 5:
                    x = up;
                    y = right;
                    break;
                case 6:
                    x = down;
                    y = right;
                    break;
                case 7:
                    x = down;
                    y = left;
                    break;
                default:
                    break;
            }
            this->setPosition(x, y);
            world->setOrganism(this->x, this->y, this);
        }
        world->setOrganism(oldX,oldY, nullptr);

        setStarvation(++starvation);
    }
    else
    {
        setStarvation(0);
    }
    setMoved(true);
    setSteps(++stepsInTime);
}

///New Issues in Zombie Spawning, crashes on start-up or after 15-50 turns
void Zombie::spawn() {
    ///DISPLAY
    world->display();

    possibleMoves.clear();

    int left = y - 1;
    int up = x - 1;
    int right = y + 1;
    int down = x + 1;

    ////Check Left
    if (left >= 0) {
        if(world->getOrganism(x,left) != nullptr)
        {
            if (world->getOrganism(x, left)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(LEFT));
            }
        }
    }
    ////Check Up
    if (up >= 0) {
        if(world->getOrganism(up, y) != nullptr) {
            if (world->getOrganism(up, y)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(UP));
            }
        }
    }
    ////Check Right
    if (right < MAXCOL) {
        if(world->getOrganism(x,right) != nullptr) {
            if (world->getOrganism(x, right)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(RIGHT));
            }
        }
    }
    ////Check Down
    if (down < MAXROW) {
        if(world->getOrganism(down,y) != nullptr) {
            if (world->getOrganism(down, y)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(DOWN));
            }
        }
    }
    ////Check NW
    if (left >= 0 && up >= 0) {
        if(world->getOrganism(up,left) != nullptr) {
            if (world->getOrganism(up, left)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(UPLEFT));
            }
        }
    }
    ////Check NE
    if (up >= 0 && right < MAXCOL) {
        if(world->getOrganism(up, right) != nullptr) {
            if (world->getOrganism(up, right)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(UPRIGHT));
            }
        }
    }
    ////Check SE
    if (right < MAXCOL && down < MAXROW) {
        if(world->getOrganism(down,right) != nullptr) {
            if (world->getOrganism(down, right)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(DOWNRIGHT));
            }
        }
    }
    ////Check SW
    if (down < MAXROW && left >= 0) {
        if(world->getOrganism(down,left) != nullptr) {
            if (world->getOrganism(down, left)->getSpecies() == HUMAN) {
                possibleMoves.push_back(moveList(DOWNLEFT));
            }
        }
    }

    if(!possibleMoves.empty())
    {
        random_shuffle(possibleMoves.begin(),possibleMoves.end());
    }
    int xPosition, yPosition;
    switch (possibleMoves[0]) {
        case 0:
            yPosition = left;
            world->setOrganism(x,yPosition,new Zombie(world, x, yPosition));
            this->setSteps(0);
            break;
        case 1:
            xPosition = up;
            world->setOrganism(xPosition,y,new Zombie(world, xPosition, y));
            this->setSteps(0);
            break;
        case 2:
            yPosition = right;
            world->setOrganism(x,yPosition,new Zombie(world, x, yPosition));
            this->setSteps(0);
            break;
        case 3:
            xPosition = down;
            world->setOrganism(xPosition,y,new Zombie(world, xPosition, y));
            this->setSteps(0);
            break;
        case 4:
            xPosition = up;
            yPosition = left;
            world->setOrganism(xPosition,yPosition,new Zombie(world, xPosition, yPosition));
            this->setSteps(0);
            break;
        case 5:
            xPosition = up;
            yPosition = right;
            world->setOrganism(xPosition,yPosition,new Zombie(world, xPosition, yPosition));
            this->setSteps(0);
            break;
        case 6:
            xPosition = down;
            yPosition = right;
            world->setOrganism(xPosition,yPosition,new Zombie(world, xPosition, yPosition));
            this->setSteps(0);
            break;
        case 7:
            xPosition = down;
            yPosition = left;
            world->setOrganism(xPosition,yPosition,new Zombie(world, xPosition, yPosition));
            this->setSteps(0);
            break;
        default:
            break;
    }
}

void Zombie::starveThisZombie() {
    world->setOrganism(this->x,this->y,new Human(world, this->x, this->y));
}

int Zombie::getStarvation() {
    return starvation;
}

void Zombie::setStarvation(int starveSteps) {
    starvation = starveSteps;
}

speciesType Zombie::getSpecies() { return ZOMBIE; }