#pragma once

#include "Actions.h"

#include <string>
#include <vector>
#include <map>

class Config
{
    public:
        static std::map<std::string, Action> keyBindings;
        
        static void init();
        static void Write(std::pair<std::string, std::string>);
        static std::vector<std::pair<std::string, std::string>> Get();
        static void loadConfig();
};