#ifndef CITY_H
#define CITY_H

#include <vector>
#include <memory>
#include "building.h"
#include "statsmanager.h"

class EventManager;
class Logger;
class FileHandler;

// Template-based city grid manager
template <typename T>
class City {
private:
    int rows;
    int cols;
    std::vector<std::vector<T*>> grid;
    StatsManager stats;
    EventManager* eventManager;
    Logger* logger;
    
    // Private helper to get building cost
    int getCost(char type) const;
    
    // Private helper to get building name
    const char* getBuildingName(char type) const;
    
public:
    City(int r = 8, int c = 10, EventManager* em = nullptr, Logger* log = nullptr);
    ~City();
    
    // Core gameplay methods
    void build(int x, int y, char type);
    void deleteBuilding(int x, int y);
    void nextTurn();
    void collectGold();
    
    // Display methods
    void showStats() const;
    void showMap() const;
    void showBuildingCosts() const;
    
    // Save/Load
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    StatsManager& getStats() { return stats; }
    const StatsManager& getStats() const { return stats; }
    T* getBuilding(int x, int y) const;
    
    // Grid serialization helpers
    std::vector<char> getGridData() const;
    void setGridData(const std::vector<char>& data);
};

#include "city_impl.h"

#endif // CITY_H