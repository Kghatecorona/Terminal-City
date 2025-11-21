#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "city.h"
#include "logger.h"

// Handles file I/O operations for saving/loading games
class FileHandler {
private:
    std::string filename;
    Logger* logger;
    
public:
    FileHandler(const std::string& fname = "city.dat", Logger* log = nullptr);
    
    // ✅ Match template version
    bool saveCity(const City<Building>& city);
    bool loadCity(City<Building>& city);
    
    bool saveFileExists() const;
    void setFilename(const std::string& fname) { filename = fname; }
};

#endif // FILEHANDLER_H