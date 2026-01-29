#include "Config.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

std::map<std::string, Action> Config::keyBindings;

void Config::init()
{
    std::string cfgFileName = "config.json";

    if (std::filesystem::is_regular_file(cfgFileName))
    {
        return;
    }

    std::ofstream file("config.json");

    nlohmann::json data;

    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 1; j < 9; j++)
        {
            data["P" + std::to_string(i) + "F" + std::to_string(j)] = { {"type", ""}, {"payload", ""} };
        }
    }

    file << std::setw(4) << data << std::endl;
}

void Config::Write(std::pair<std::string, std::string> keyvalue)
{
    std::ifstream inFile("config.wcfg");
    std::vector<std::string> buffer;
    std::string line;

    if (inFile.is_open())
    {
        while (std::getline(inFile, line)) 
        {
            std::vector<std::string> data = Utils::Split(line, '|'); 

            if (!data.empty() && data[0] == keyvalue.first)
            {
                std::string newLine = keyvalue.first + "|" + keyvalue.second;
                buffer.push_back(newLine);
            }
            else
            {
                buffer.push_back(line);
            }
        }
        inFile.close();
    }

    std::ofstream outFile("config.wcfg");
    if (outFile.is_open())
    {
        for (const auto& str : buffer)
        {
            outFile << str << '\n';
        }
        outFile.close();
    }
}

std::vector<std::pair<std::string, std::string>> Config::Get()
{
    std::vector<std::pair<std::string, std::string>> buffer;
    std::ifstream outFile("config.wcfg");
    std::string line;

    if (outFile.is_open())
    {
        while (std::getline(outFile, line)) 
        {
            if (line.empty()) continue;

            std::vector<std::string> split = Utils::Split(line, '|');
            
            if (split.size() >= 2)
            {
                buffer.push_back(std::make_pair(split[0], split[1]));
            }
            else if (split.size() == 1)
            {
                buffer.push_back(std::make_pair(split[0], ""));
            }
        }
        outFile.close();
    }

    return buffer;
}

void Config::loadConfig() 
{
    keyBindings["P0F1"] = { CMD_MEDIA_PREV, "" };
    keyBindings["P0F2"] = { CMD_MEDIA_PLAY_PAUSE, "" };
    keyBindings["P0F3"] = { CMD_MEDIA_NEXT, "" };
    keyBindings["P0F4"] = { CMD_VOLUME_UP, "" };
    keyBindings["P0F5"] = { CMD_OPEN_URL, "http://192.168.0.10" };
    keyBindings["P0F6"] = { CMD_RUN_APP, "notepad.exe" };
    keyBindings["P0F7"] = { CMD_VOLUME_MUTE, "" };
    keyBindings["P0F8"] = { CMD_VOLUME_DOWN, "" };
}