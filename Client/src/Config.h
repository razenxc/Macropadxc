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
        static void write(std::pair<std::string, Action> keyAction);
        static void loadConfig();
};