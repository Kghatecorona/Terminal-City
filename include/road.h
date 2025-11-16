#ifndef ROAD_H
#define ROAD_H

#include "building.h"

// Road building class (infrastructure, no production)
class Road : public Building {
public:
    char getSymbol() const override;
    int produceGold() const override;
    const char* getName() const override;
};

#endif // ROAD_H