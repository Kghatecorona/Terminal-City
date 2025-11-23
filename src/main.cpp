#include <iostream>
#include <string>
#include <cctype>
#include "city.h"
#include "eventmanager.h"
#include "filehandler.h"
#include "logger.h"
#include "building.h"

// Input validation helper
int getValidInt(int min, int max) {
    int input;
    while (!(std::cin >> input) || input < min || input > max) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please enter a number between "
                  << min << " and " << max << ": ";
    }
    return input;
}

// Display main menu
void displayMainMenu() {
    std::cout << "\n========== TERMINAL CITY MENU =========\n";
    std::cout << "1. Build Infrastructure\n";
    std::cout << "2. Demolish Building\n";
    std::cout << "3. Next Turn\n";
    std::cout << "4. Save Game\n";
    std::cout << "5. Load Game\n";
    std::cout << "6. Show Building Costs\n";
    std::cout << "7. Exit Game\n";
    std::cout << "========================================\n";
    std::cout << "> ";
}

// Main game loop
int main() {
    std::cout << "\n*** TERMINAL CITY - Command-Line Civilization Game ***\n\n";
    
    // Initialize logger
    Logger logger("game.log");
    logger.info("Terminal City launched");
    
    // Initialize event manager
    EventManager eventManager(&logger);
    
    // Initialize city with template specialization
    City<Building> city(8, 10, &eventManager, &logger);
    logger.info("City initialized: 8x10 grid");
    
    // Initialize file handler
    FileHandler fileHandler("city.dat", &logger);
    
    // Ask to load saved game
    int choice = 0;
    if (fileHandler.saveFileExists()) {
        std::cout << "Saved game found! Load it? (1=Yes, 0=No): ";
        choice = getValidInt(0, 1);
        if (choice == 1) {
            city.loadFromFile("city.dat");
        }
    }
    
    // Main game loop
    do {
        city.showStats();
        city.showMap();
        displayMainMenu();
        
        choice = getValidInt(1, 7);
        
        switch (choice) {
            case 1: {
                // Build infrastructure
                city.showBuildingCosts();
                std::cout << "Enter position (row col): ";
                int x = getValidInt(0, city.getRows() - 1);
                int y = getValidInt(0, city.getCols() - 1);
                std::cout << "Building type (R/I/F/=): ";
                char type;
                std::cin >> type;
                type = std::toupper(type);
                city.build(x, y, type);
                break;
            }
            
            case 2: {
                // Demolish building
                std::cout << "Enter position (row col): ";
                int x = getValidInt(0, city.getRows() - 1);
                int y = getValidInt(0, city.getCols() - 1);
                city.deleteBuilding(x, y);
                break;
            }
            
            case 3: {
                // Next turn
                city.nextTurn();
                std::cout << "\n*** Turn ended! ***\n";
                break;
            }
            
            case 4: {
                // Save game
                city.saveToFile("city.dat");
                break;
            }
            
            case 5: {
                // Load game
                city.loadFromFile("city.dat");
                break;
            }
            
            case 6: {
                // Show building costs
                city.showBuildingCosts();
                break;
            }
            
            case 7: {
                // Exit
                std::cout << "\nSaving game before exit...\n";
                city.saveToFile("city.dat");
                std::cout << "Thanks for playing Terminal City! Goodbye.\n";
                logger.info("Game exited normally");
                break;
            }
        }
        
    } while (choice != 7);
    
    return 0;
}