#include "residential.h"

char Residential::getSymbol() const {
    return 'R';
}

int Residential::produceGold() const {
    return 0;
}

const char* Residential::getName() const {
    return "Residential";
}