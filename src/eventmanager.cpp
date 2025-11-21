#include "eventmanager.h"
#include "statsmanager.h"
#include "logger.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

EventManager::EventManager(Logger* log)
    : eventChance(25), logger(log) {
    srand(time(0));
}

void EventManager::triggerRandomEvent(StatsManager& stats) {
    int randomValue = rand() % 100;
    
    if (randomValue < eventChance) {
        int eventType = rand() % 4;
        
        switch (eventType) {
            case 0: // Storm disaster
                std::cout << "\n*** DISASTER: A severe storm struck! ***\n";
                stats.adjustPopulation(-300);
                stats.subtractGold(200);
                stats.adjustEnvironment(-15);
                if (logger) logger->warning("Storm disaster occurred");
                break;
                
            case 1: // Fire disaster
                std::cout << "\n*** DISASTER: A massive fire broke out! ***\n";
                stats.subtractGold(300);
                stats.adjustEnvironment(-10);
                if (logger) logger->warning("Fire disaster occurred");
                break;
                
            case 2: // Positive event - Migration
                std::cout << "\n*** GOOD NEWS: Population migration incoming! ***\n";
                stats.addPopulation(400);
                stats.adjustHappiness(10);
                if (logger) logger->info("Migration event occurred");
                break;
                
            case 3: // Positive event - Trade
                std::cout << "\n*** GOOD NEWS: Profitable trade deal! ***\n";
                stats.addGold(250);
                stats.adjustHappiness(5);
                if (logger) logger->info("Trade event occurred");
                break;
        }
    }
}

void EventManager::setEventChance(int chance) {
    eventChance = (chance > 0 && chance <= 100) ? chance : 25;
}