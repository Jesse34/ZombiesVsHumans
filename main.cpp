#include <iostream>
#include <string>
#include <unistd.h>
#include "World.h"
#include "Human.h"
#include "Zombie.h"

int main() {
    World world = World();

    do {
        world.gameCycle();

        world.display();

        usleep(200000);
    }
    while (!world.checkExtinction() && world.count <= 10000);

    return 0;
}