#include "Config.h"
#include "SystemUtils.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace nlohmann;

std::map<std::string, Action> Config::keyBindings;
std::filesystem::file_time_type Config::_lastWriteTime;

std::string cfgFilename = SystemUtils::getExecutableDir() + "/" + "config.json";

void Config::init()
{
    std::string cfgFileName = cfgFilename;

    if (std::filesystem::is_regular_file(cfgFileName))
    {
        return;
    }

    std::ofstream file(cfgFilename);

    json data;

   for (size_t j = 1; j < 9; j++)
    {
        data["F" + std::to_string(j)] = { {"type", ""}, {"payload", ""} };
    }

    data["F1"] = { {"type", CMD_MEDIA_PREV},       {"payload", ""} };
    data["F2"] = { {"type", CMD_MEDIA_PLAY_PAUSE}, {"payload", ""} };
    data["F3"] = { {"type", CMD_MEDIA_NEXT},       {"payload", ""} };
    data["F4"] = { {"type", CMD_VOLUME_UP},        {"payload", ""} };
    data["F5"] = { {"type", CMD_OPEN_URL},         {"payload", "https://google.com"} };
    data["F6"] = { {"type", CMD_RUN_APP},          {"payload", "notepad.exe"} };
    data["F7"] = { {"type", CMD_VOLUME_MUTE},      {"payload", ""} };
    data["F8"] = { {"type", CMD_VOLUME_DOWN},      {"payload", ""} };

    file << std::setw(4) << data << std::endl;
}

void Config::write(std::pair<std::string, Action> keyAction)
{
    std::ifstream f(cfgFilename);
    json data;

    try 
    {
        data = json::parse(f);
    }
    catch (const json::parse_error& e) 
    {
        std::cerr << "[Error][Config::write()] JSON Parse Error: " << e.what() << std::endl;
        return;
    }
    
    f.close();
    data[keyAction.first]["type"] = keyAction.second.type;
    data[keyAction.first]["payload"] = keyAction.second.payload;

    std::ofstream ff(cfgFilename);
    ff << std::setw(4) << data << std::endl;
}

void Config::loadConfig() 
{
    if (std::filesystem::exists(cfgFilename)) 
    {
        _lastWriteTime = std::filesystem::last_write_time(cfgFilename);
    }
    
    std::ifstream file(cfgFilename);
    if (!file.is_open()) return;

    json data;
    try 
    {
        file >> data;
    }
    catch (const json::parse_error& e) 
    {
        std::cerr << "[Error][Config::loadConfig()] JSON Corrupted: " << e.what() << std::endl;
        return;
    }

    keyBindings.clear();

    for (auto it = data.begin(); it != data.end(); it++) 
    {
        std::string key = it.key();
        json value = it.value();

        try 
        {
            int typeInt = 0;

            if (value["type"].is_number()) 
            {
                typeInt = value["type"];
            } 
            else 
            {
                continue;
            }
            
            std::string payload = "";
            if (value.contains("payload")) 
            {
                payload = value["payload"];
            }

            keyBindings[key] = { (ActionType)typeInt, payload };
        }
        catch (const std::exception& e) 
        {
            std::cerr << "[Error][Config::loadConfig()] Error loading " << key << ": " << e.what() << std::endl;
        }
    }
}

void Config::hotReload()
{
    if (!std::filesystem::exists(cfgFilename)) return;

    try
    {
        auto currentWriteTime = std::filesystem::last_write_time(cfgFilename);
        if (currentWriteTime > _lastWriteTime)
        {
            std::cout << "[Status][Config::hotReload()] Change detected! Reloading..." << std::endl;
            loadConfig();
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "[Warning][Config::hotReload()] Could not check file time (locked?): " << e.what() << std::endl;
    }
}