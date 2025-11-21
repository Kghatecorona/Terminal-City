#ifndef CITY_IMPL_H
#define CITY_IMPL_H

#include "city.h"
#include "building.h"
#include "residential.h"
#include "industrial.h"
#include "farm.h"
#include "road.h"
#include "eventmanager.h"
#include "logger.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// City template implementation
template <typename T>
City<T>::City(int r, int c, EventManager* em, Logger* log)
    : rows(r), cols(c), eventManager(em), logger(log) {
    grid.resize(rows, std::vector<T*>(cols, nullptr));
    stats.setGold(1000);
    stats.setPopulation(5000);
    stats.setHappiness(75);
    stats.setEnvironment(80);
    
    if (logger) logger->info("City initialized: " + std::to_string(rows) + 
                             "x" + std::to_string(cols));
}

template <typename T>
City<T>::~City() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
    }
    if (logger) logger->info("City destroyed");
}

template <typename T>
int City<T>::getCost(char type) const {
    switch (type) {
        case 'R': return 200;  // Residential
        case 'I': return 300;  // Industrial
        case 'F': return 150;  // Farm
        case '=': return 100;  // Road
        default: return 0;
    }
}

template <typename T>
const char* City<T>::getBuildingName(char type) const {
    switch (type) {
        case 'R': return "Residential";
        case 'I': return "Industrial";
        case 'F': return "Farm";
        case '=': return "Road";
        default: return "Unknown";
    }
}

template <typename T>
void City<T>::build(int x, int y, char type) {
    try {
        if (x < 0 || y < 0 || x >= rows || y >= cols) {
            throw InvalidCoordinateException("Coordinates out of range!");
        }
        if (grid[x][y] != nullptr) {
            std::cout << "That spot already has a building!\n";
            if (logger) logger->warning("Build attempted on occupied cell");
            return;
        }
        
        int cost = getCost(type);
        if (cost == 0) {
            throw InvalidInputException("Invalid building type!");
        }
        if (stats.getGold() < cost) {
            throw InsufficientFundsException("Insufficient gold! Need " + 
                                             std::to_string(cost));
        }
        
        T* building = nullptr;
        switch (type) {
            case 'R': building = new Residential(); 
                      stats.addPopulation(500); break;
            case 'I': building = new Industrial(); break;
            case 'F': building = new Farm(); break;
            case '=': building = new Road(); break;
        }
        
        grid[x][y] = building;
        stats.subtractGold(cost);
        
        std::cout << "Building " << getBuildingName(type) << " placed at (" 
                  << x << "," << y << "). Cost: -" << cost << " gold.\n";
        
        if (logger) logger->info(std::string("Built ") + getBuildingName(type));
        
    } catch (const InvalidCoordinateException& e) {
        std::cout << "Error: " << e.what() << "\n";
        if (logger) logger->error(std::string("InvalidCoordinate: ") + e.what());
    } catch (const InsufficientFundsException& e) {
        std::cout << "Error: " << e.what() << "\n";
        if (logger) logger->warning(std::string("InsufficientFunds: ") + e.what());
    } catch (const InvalidInputException& e) {
        std::cout << "Error: " << e.what() << "\n";
        if (logger) logger->error(std::string("InvalidInput: ") + e.what());
    }
}

template <typename T>
void City<T>::deleteBuilding(int x, int y) {
    try {
        if (x < 0 || y < 0 || x >= rows || y >= cols) {
            throw InvalidCoordinateException("Coordinates out of range!");
        }
        if (grid[x][y] == nullptr) {
            std::cout << "No building at that location!\n";
            if (logger) logger->warning("Delete attempted on empty cell");
            return;
        }
        
        char symbol = grid[x][y]->getSymbol();
        int refund = getCost(symbol) / 2;
        
        if (symbol == 'R') {
            stats.addPopulation(-500);
            if (stats.getPopulation() < 0) {
                stats.setPopulation(0);
            }
        }
        
        delete grid[x][y];
        grid[x][y] = nullptr;
        stats.addGold(refund);
        
        std::cout << "Building demolished. Refund: +" << refund << " gold.\n";
        if (logger) logger->info("Demolished building");
        
    } catch (const InvalidCoordinateException& e) {
        std::cout << "Error: " << e.what() << "\n";
        if (logger) logger->error(std::string("DeleteFailed: ") + e.what());
    }
}

template <typename T>
void City<T>::collectGold() {
    int production = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != nullptr) {
                production += grid[i][j]->produceGold();
            }
        }
    }
    stats.addGold(production);
    std::cout << "Production this turn: +" << production << " gold coins\n";
    if (logger) logger->info("Gold collected: " + std::to_string(production));
}

template <typename T>
void City<T>::nextTurn() {
    stats.nextTurn();
    collectGold();
    if (eventManager) {
        eventManager->triggerRandomEvent(stats);
    }
    if (logger) logger->info("Turn advanced to " + std::to_string(stats.getTurn()));
}

template <typename T>
void City<T>::showStats() const {
    std::cout << "\n" << stats.getStatsString() << "\n";
}

template <typename T>
void City<T>::showMap() const {
    std::cout << "\nCity Map (Turn " << stats.getTurn() << "):\n";
    std::cout << "  ";
    for (int j = 0; j < cols; ++j) std::cout << j << " ";
    std::cout << "\n";
    
    for (int i = 0; i < rows; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != nullptr) {
                std::cout << grid[i][j]->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

template <typename T>
void City<T>::showBuildingCosts() const {
    std::cout << "\n--- Building Types & Production ---\n";
    std::cout << "R: Residential (Cost: 200, Population: +500)\n";
    std::cout << "I: Industrial  (Cost: 300, Gold/turn: +100)\n";
    std::cout << "F: Farm        (Cost: 150, Gold/turn: +50)\n";
    std::cout << "=: Road        (Cost: 100, No production)\n";
    std::cout << "------------------------------------\n";
}

template <typename T>
void City<T>::saveToFile(const std::string& filename) {
    try {
        std::ofstream fout(filename, std::ios::binary);
        if (!fout) {
            throw FileOperationException("Cannot open file for writing: " + filename);
        }
        
        fout.write((char*)&rows, sizeof(rows));
        fout.write((char*)&cols, sizeof(cols));
        
        int pop = stats.getPopulation();
        int gold = stats.getGold();
        int turn = stats.getTurn();
        int happiness = stats.getHappiness();
        int environment = stats.getEnvironment();
        
        fout.write((char*)&pop, sizeof(pop));
        fout.write((char*)&gold, sizeof(gold));
        fout.write((char*)&turn, sizeof(turn));
        fout.write((char*)&happiness, sizeof(happiness));
        fout.write((char*)&environment, sizeof(environment));
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char symbol = grid[i][j] ? grid[i][j]->getSymbol() : '.';
                fout.write(&symbol, sizeof(symbol));
            }
        }
        
        fout.close();
        std::cout << "Game saved successfully to " << filename << ".\n";
        if (logger) logger->info("Game saved to " + filename);
        
    } catch (const FileOperationException& e) {
        std::cout << "Save Error: " << e.what() << "\n";
        if (logger) logger->error(std::string("SaveFailed: ") + e.what());
    }
}

template <typename T>
void City<T>::loadFromFile(const std::string& filename) {
    try {
        std::ifstream fin(filename, std::ios::binary);
        if (!fin) {
            throw FileOperationException("Cannot open file for reading: " + filename);
        }
        
        int loadRows, loadCols;
        fin.read((char*)&loadRows, sizeof(loadRows));
        fin.read((char*)&loadCols, sizeof(loadCols));
        
        if (loadRows != rows || loadCols != cols) {
            throw FileOperationException("Mismatched grid size in save file");
        }
        
        int pop, gold, turn, happiness, environment;
        fin.read((char*)&pop, sizeof(pop));
        fin.read((char*)&gold, sizeof(gold));
        fin.read((char*)&turn, sizeof(turn));
        fin.read((char*)&happiness, sizeof(happiness));
        fin.read((char*)&environment, sizeof(environment));
        
        stats.setPopulation(pop);
        stats.setGold(gold);
        stats.setHappiness(happiness);
        stats.setEnvironment(environment);
        
        for (int i = 0; i < turn; ++i) {
            stats.nextTurn();
        }
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char symbol;
                fin.read(&symbol, sizeof(symbol));
                
                if (symbol != '.') {
                    if (symbol == 'R') grid[i][j] = new Residential();
                    else if (symbol == 'I') grid[i][j] = new Industrial();
                    else if (symbol == 'F') grid[i][j] = new Farm();
                    else if (symbol == '=') grid[i][j] = new Road();
                }
            }
        }
        
        fin.close();
        std::cout << "Game loaded successfully from " << filename << ".\n";
        if (logger) logger->info("Game loaded from " + filename);
        
    } catch (const FileOperationException& e) {
        std::cout << "Load Error: " << e.what() << "\n";
        if (logger) logger->error(std::string("LoadFailed: ") + e.what());
    }
}

template <typename T>
T* City<T>::getBuilding(int x, int y) const {
    if (x < 0 || y < 0 || x >= rows || y >= cols) return nullptr;
    return grid[x][y];
}

template <typename T>
std::vector<char> City<T>::getGridData() const {
    std::vector<char> data;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char symbol = grid[i][j] ? grid[i][j]->getSymbol() : '.';
            data.push_back(symbol);
        }
    }
    return data;
}

template <typename T>
void City<T>::setGridData(const std::vector<char>& data) {
    if (data.size() != rows * cols) return;
    
    int idx = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char symbol = data[idx++];
            if (symbol != '.') {
                if (symbol == 'R') grid[i][j] = new Residential();
                else if (symbol == 'I') grid[i][j] = new Industrial();
                else if (symbol == 'F') grid[i][j] = new Farm();
                else if (symbol == '=') grid[i][j] = new Road();
            }
        }
    }
}

#endif // CITY_IMPL_H