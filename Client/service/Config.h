#pragma once

#include "Actions.h"

#include <string>
#include <vector>
#include <map>
#include <filesystem>

class Config
{
    public:
        static std::map<std::string, Action> keyBindings;
        
        static void init();
        static void write(std::pair<std::string, Action> keyAction);
        static void loadConfig();
        static void hotReload();

    private:
        static std::filesystem::file_time_type _lastWriteTime;
};