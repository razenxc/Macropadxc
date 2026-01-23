#include "Utils.h"

#include <sstream>

namespace Utils
{
    std::vector<std::string> Split(std::string data, char ch)
    {
        std::vector<std::string> result;
        std::stringstream ss(data);
        std::string item;

        while (std::getline(ss, item, ch)) 
        {
            result.push_back(item);
        }

        return result;
    }
}