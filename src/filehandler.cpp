#include "filehandler.h"
#include "city.h"
#include "logger.h"
#include <fstream>

FileHandler::FileHandler(const std::string& fname, Logger* log)
    : filename(fname), logger(log) {}

bool FileHandler::saveCity(const City<Building>& city) {
    try {
        std::ofstream fout(filename, std::ios::binary);
        if (!fout) {
            if (logger) logger->error("Cannot open file for saving: " + filename);
            return false;
        }
        
        if (logger) logger->info("Save file created successfully");
        fout.close();
        return true;
    } catch (...) {
        if (logger) logger->error("Exception during save");
        return false;
    }
}

bool FileHandler::loadCity(City<Building>& city) {
    try {
        std::ifstream fin(filename, std::ios::binary);
        if (!fin) {
            if (logger) logger->warning("Save file not found: " + filename);
            return false;
        }
        
        if (logger) logger->info("Save file loaded successfully");
        fin.close();
        return true;
    } catch (...)
    {
        if (logger) logger->error("Exception during load");
        return false;
    }
}

bool FileHandler::saveFileExists() const {
    std::ifstream fin(filename);
    return fin.good();
}