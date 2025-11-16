#include "industrial.h"

char Industrial::getSymbol() const {
    return 'I';
}

int Industrial::produceGold() const {
    return 100;
}

const char* Industrial::getName() const {
    return "Industrial";
}