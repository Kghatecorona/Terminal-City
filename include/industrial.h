#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.h"

// Industrial building class (high gold production)
class Industrial : public Building {
public:
    char getSymbol() const override;
    int produceGold() const override;
    const char* getName() const override;
};

#endif // INDUSTRIAL_H