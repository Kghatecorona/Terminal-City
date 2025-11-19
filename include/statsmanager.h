#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <string>

// Manages city statistics
class StatsManager {
private:
    int population;
    int gold;
    int happiness;
    int environment;
    int turn;
    
public:
    StatsManager();
    
    // Getters
    int getPopulation() const { return population; }
    int getGold() const { return gold; }
    int getHappiness() const { return happiness; }
    int getEnvironment() const { return environment; }
    int getTurn() const { return turn; }
    
    // Setters and Adjusters with validation
    void setPopulation(int pop);
    void addPopulation(int pop);
    void adjustPopulation(int pop);   // ✅ Added this line

    void setGold(int g);
    void addGold(int g);
    void subtractGold(int g);
    
    void setHappiness(int h);
    void adjustHappiness(int h);
    
    void setEnvironment(int e);
    void adjustEnvironment(int e);
    
    void nextTurn();
    
    // Display stats
    std::string getStatsString() const;
};

#endif // STATSMANAGER_H