#include "farm.h"

char Farm::getSymbol() const {
    return 'F';
}

int Farm::produceGold() const {
    return 50;
}

const char* Farm::getName() const {
    return "Farm";
}