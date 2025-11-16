#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.h"

// Industrial building class (high gold production)
class Industrial : public Building {
public:
    char getSymbol() const override;
    int produceGold() const;
    const char* getName() const;
};

#endif // INDUSTRIAL_H