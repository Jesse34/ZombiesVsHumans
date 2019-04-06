#include <iostream>
#include <string>
#include <unistd.h>
#include "World.h"
#include "Human.h"
#include "Zombie.h"

using namespace std;

int main() {
    World world = World();

    do {
        world.gameCycle();

        world.display();

        usleep(500000);
    }
    while (!world.checkExtinction() && world.count <= 10000);

    return 0;
}