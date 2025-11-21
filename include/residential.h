#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "building.h"

// Residential building class (produces population)
class Residential : public Building {
public:
    char getSymbol() const override;
    int produceGold() const override;
    const char* getName() const override;
};

#endif // RESIDENTIAL_H