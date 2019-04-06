#include <iostream>
#include <random>
#include "World.h"
#include "Human.h"
#include "Zombie.h"

World::World() {
    Organism *grid[MAXROW][MAXCOL];

    nullifyWorld();
    populateWorld();
}

World::~World() {}

void World::gameCycle() {
    setMovedToFalse();
    moveOrganisms();
    count++;
    countOrganisms();

    convertZombies();
    spawnOrganisms();
    starveZombies();

    checkExtinction();
}

///POPULATE WORLD
void World::populateWorld() {

    //Setup Random Int Generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,ARRAYSIZE-1);

    bool organismSet = false;

    for(int i=0;i<INITHUMANS;i++){
        int randomX;
        int randomY;

        organismSet = false;
        randomX = dis(gen);
        randomY = dis(gen);


        Organism* newHuman = new Human(this, randomX, randomY);
        if (grid[randomX][randomY] == nullptr)
        {
            grid[randomX][randomY] = newHuman;
            organismSet = true;
        }
    }
    while (!organismSet);

    for(int i=0;i<INITZOMBIES;i++){
        int randomX;
        int randomY;

        bool organismSet = false;
        do {
            randomX = dis(gen);
            randomY = dis(gen);
            Organism* newZombie = new Zombie(this, randomX, randomY);
            if (grid[randomX][randomY] == nullptr)
            {
                grid[randomX][randomY] = newZombie;
                organismSet = true;
            }
        }
        while (!organismSet);
    }
}
///END POPULATE WORLD

///MOVE ORGANISMS
void World::moveOrganisms() {
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++) {
            if (grid[x][y] != nullptr && !grid[x][y]->getMoved() && grid[x][y]->getSpecies() == ZOMBIE){
                grid[x][y]->move();
            }
        }
    }
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++) {
            if (grid[x][y] != nullptr && !grid[x][y]->getMoved() && grid[x][y]->getSpecies() == HUMAN){
                grid[x][y]->move();
            }
        }
    }
}
///END MOVE ORGANISMS

void World::convertZombies() {
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++) {
            if (grid[x][y] != nullptr) {
                if (grid[x][y]->getSpecies() == ZOMBIE) {
                    if (grid[x][y]->getSteps() >= SPAWNZOMBIES) {
                        grid[x][y]->spawn();
                    }
                }
            }
        }
    }
}

void World::starveZombies() {
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++) {
            if (grid[x][y] != nullptr) {
                if (grid[x][y]->getSpecies() == ZOMBIE) {
                    if (((Zombie*) grid[x][y])->getStarvation() >= STARVEZOMBIE) {
                        ((Zombie*) grid[x][y])->starveThisZombie();
                    }
                }
            }
        }
    }
}

void World::spawnOrganisms()
{
    for(int x=0;x < MAXROW;x++)
    {
        for (int y = 0; y < MAXCOL; y++)
        {
            if(grid[x][y] != nullptr)
            {
                if(grid[x][y]->getSpecies() == HUMAN)
                {
                    if(grid[x][y]->getSteps() >= SPAWNHUMANS)
                    {
                        ///{ LEFT, UP, RIGHT, DOWN, UPLEFT, UPRIGHT, DOWNRIGHT,  DOWNLEFT }
                        vector<int> possibleSpawns;

                        int spawnX = -1;
                        int spawnY = -1;

                        possibleSpawns.clear();
                        int left = y-1;
                        int up = x-1;
                        int right = y+1;
                        int down = x+1;

                        ////Check Left
                        if(left >= 0) {
                            if (getOrganism(x,left) == nullptr) {
                                possibleSpawns.push_back(3);
                            }
                        }
                        ////Check Up
                        if(up >= 0) {
                            if (getOrganism(up,y) == nullptr) {
                                possibleSpawns.push_back(1);
                            }
                        }
                        ////Check Right
                        if(right < MAXCOL) {
                            if (getOrganism(x,right) == nullptr) {
                                possibleSpawns.push_back(5);
                            }
                        }
                        ////Check Down
                        if(down < MAXROW) {
                            if (getOrganism(down,y) == nullptr) {
                                possibleSpawns.push_back(7);
                            }
                        }

                        if(!possibleSpawns.empty()){
                            int moveSelection = returnRandom(static_cast<int>(possibleSpawns.size() - 1));


                            switch(possibleSpawns[moveSelection]){
                                case 3:
                                    spawnY = left;
                                    spawnX = x;
                                    break;
                                case 1:
                                    spawnX = up;
                                    spawnY = y;
                                    break;
                                case 5:
                                    spawnY = right;
                                    spawnX = x;
                                    break;
                                case 7:
                                    spawnX = down;
                                    spawnY = y;
                                    break;
                                default:
                                    break;
                            }

                            if(spawnX != -1 && spawnY != -1 )
                            {
                                Organism* newHuman = new Human(this, spawnX, spawnY);
                                grid[spawnX][spawnY] = newHuman;
                            }
                            grid[x][y]->setSteps(0);
                        }
                    }
                }
            }
        }
    }
}

///DISPLAY METHOD
void World::display() const {
    cout << "\n\n\n";
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){

            //cout << "|";
            if(this->grid[x][y] != nullptr){
                if(this->grid[x][y]->getSpecies() == HUMAN)
                {
                    cout << H2;
                }
                else if(this->grid[x][y]->getSpecies() == ZOMBIE)
                {
                    cout << Z2;
                }
            }
            else
            {
                cout << EMPTY;
            }
        }
        cout //<< "|"
             << endl;
    }
    cout << "\nHumans: " << numOfHumans << " " << H2 << " | " <<
         "Zombies: "<< numOfZombies << " " << Z2 << " | " <<
         "Turn: "   << count << endl;
}
///END DISPLAY METHOD

Organism *World::getOrganism(int x, int y) const {
    return grid[x][y];
}

void World::setOrganism(int x, int y, Organism* thisOrganism) {
    if((x >= 0) && (x < ARRAYSIZE) && (y >= 0) && (y < ARRAYSIZE)) {
        grid[x][y] = thisOrganism;
    }
}

void World::countOrganisms() {
    numOfHumans = 0;
    numOfZombies = 0;
    for(int x=0;x < MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            if(grid[x][y] != nullptr) {
                if (grid[x][y]->getSpecies() == HUMAN) {
                    numOfHumans++;
                } else if (grid[x][y]->getSpecies() == ZOMBIE) {
                    numOfZombies++;
                }
            }
        }
    }
}

void World::setMovedToFalse() {
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++) {
            if (grid[x][y] != nullptr){
                grid[x][y]->setMoved(false);
            }
        }
    }
}

void World::nullifyWorld() {
    for(int x=0;x<MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            grid[x][y] = nullptr;
        }
    }
}

int World::returnRandom(int thisNumber) const {
    //Setup Random Int Generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, thisNumber);

    return dis(gen);
}

bool World::checkExtinction() {
    return (numOfHumans <= 0 || numOfZombies <= 0);
}




