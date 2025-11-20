#include "statsmanager.h"
#include <algorithm>
#include <sstream>

StatsManager::StatsManager()
    : population(5000), gold(1000), happiness(75), 
      environment(80), turn(1) {}

void StatsManager::setPopulation(int pop) {
    population = std::max(0, pop);
}

void StatsManager::addPopulation(int pop) {
    population = std::max(0, population + pop);
}

void StatsManager::adjustPopulation(int pop) {   // ✅ New function
    population = std::max(0, population + pop);
}

void StatsManager::setGold(int g) {
    gold = std::max(0, g);
}

void StatsManager::addGold(int g) {
    gold = std::max(0, gold + g);
}

void StatsManager::subtractGold(int g) {
    gold = std::max(0, gold - g);
}

void StatsManager::setHappiness(int h) {
    happiness = std::max(0, std::min(100, h));
}

void StatsManager::adjustHappiness(int h) {
    happiness = std::max(0, std::min(100, happiness + h));
}

void StatsManager::setEnvironment(int e) {
    environment = std::max(0, std::min(100, e));
}

void StatsManager::adjustEnvironment(int e) {
    environment = std::max(0, std::min(100, environment + e));
}

void StatsManager::nextTurn() {
    turn++;
}

std::string StatsManager::getStatsString() const {
    std::ostringstream oss;
    oss << "===== CITY STATS - TURN " << turn << " =====\n"
        << "Population: " << population << "\n"
        << "Gold: " << gold << " coins\n"
        << "Happiness: " << happiness << "%\n"
        << "Environment: " << environment << "%\n"
        << "========================================";
    return oss.str();
}