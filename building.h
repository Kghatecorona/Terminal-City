#ifndef BUILDING_H
#define BUILDING_H

class Building {
public:
    virtual char getSymbol() const = 0;
    virtual ~Building() = default;
};

#endif
