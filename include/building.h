#ifndef BUILDING_H
#define BUILDING_H

// Abstract base class for all building types
class Building {
public:
    // Pure virtual function to get building symbol
    virtual char getSymbol() const = 0;
    
    // Pure virtual function to get production per turn
    virtual int produceGold() const = 0;
    
    // Get building name for logging
    virtual const char* getName() const = 0;
    
    // Virtual destructor
    virtual ~Building() {}
};

#endif // BUILDING_H    
