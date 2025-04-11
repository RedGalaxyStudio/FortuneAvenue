#pragma once
#include <fstream>
#include <string>

class Logger {
public:
    static void log(const std::string& msg) {
        std::ofstream file("game_log.txt", std::ios::app);
        file << msg << std::endl;
    }
};
