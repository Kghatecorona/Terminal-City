#ifndef FARM_H
#define FARM_H

#include "building.h"

// Farm building class (moderate gold production)
class Farm : public Building {
public:
    char getSymbol() const override;
    int produceGold() const override;
    const char* getName() const override;
};

#endif // FARM_H