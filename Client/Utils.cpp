#include "Utils.h"

#include <sstream>

namespace Utils
{
    std::vector<std::string> Split(std::string data)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(data);
        std::string token;
        
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
}