#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class StatsManager;
class Logger;

// Manages random events in the city
class EventManager {
private:
    int eventChance; // Percentage chance for event
    Logger* logger;
    
public:
    EventManager(Logger* log = nullptr);
    
    // Trigger random event each turn
    void triggerRandomEvent(StatsManager& stats);
    
    // Set event chance (1-100 represents percentage)
    void setEventChance(int chance);
};

#endif // EVENTMANAGER_H