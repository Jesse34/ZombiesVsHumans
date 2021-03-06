#include "Organism.h"

Organism::Organism() {}

Organism::Organism(World *world, int xPos, int yPos) {}

Organism::~Organism() {}

bool Organism::getMoved() const {
    return moved;
}

void Organism::setMoved(bool oneStep) {
    this->moved = oneStep;
}

bool Organism::getHasSpawned() {
    return false;
}

int Organism::getSteps() {
    return stepsInTime;
}

void Organism::setSteps(int aStepInTime) {
    stepsInTime = aStepInTime;
}

void Organism::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Organism::setHasSpawned(bool hasSpawned) {}