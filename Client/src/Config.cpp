#include "Config.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace nlohmann;

std::map<std::string, Action> Config::keyBindings;
std::string cfgFilename = "config.json";

void Config::init()
{
    std::string cfgFileName = cfgFilename;

    if (std::filesystem::is_regular_file(cfgFileName))
    {
        return;
    }

    std::ofstream file(cfgFilename);

    json data;

    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 1; j < 9; j++)
        {
            data["P" + std::to_string(i) + "F" + std::to_string(j)] = { {"type", ""}, {"payload", ""} };
        }
    }

    file << std::setw(4) << data << std::endl;
}

void Config::write(std::pair<std::string, Action> keyAction)
{
    std::ifstream f(cfgFilename);
    json data;

    try {
        data = json::parse(f);
    } catch (const json::parse_error& e) {
        std::cerr << "[Config::init()]JSON Parse Error: " << e.what() << std::endl;
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
    // Mock config
    Config::write({"P0F1", {CMD_MEDIA_PREV, ""}});
    Config::write({"P0F2", {CMD_MEDIA_PLAY_PAUSE, ""}});
    Config::write({"P0F3", {CMD_MEDIA_NEXT, ""}});
    Config::write({"P0F4", {CMD_VOLUME_UP, ""}});
    Config::write({"P0F5", {CMD_OPEN_URL, "http://192.168.0.10"}});
    Config::write({"P0F6", {CMD_RUN_APP, "notepad.exe"}});
    Config::write({"P0F7", {CMD_VOLUME_MUTE, ""}});
    Config::write({"P0F8", {CMD_VOLUME_DOWN, ""}});

    // Function implementation
    std::ifstream file(cfgFilename);
    if (!file.is_open()) return;

    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        std::cerr << "[Config::loadConfig()] JSON Corrupted: " << e.what() << std::endl;
        return;
    }

    keyBindings.clear();

    for (auto it = data.begin(); it != data.end(); it++) 
    {
        std::string key = it.key();
        json value = it.value();

        try {
            int typeInt = 0;

            if (value["type"].is_number()) {
                typeInt = value["type"];
            } else {
                continue;
            }
            
            std::string payload = "";
            if (value.contains("payload")) {
                payload = value["payload"];
            }

            keyBindings[key] = { (ActionType)typeInt, payload };
        }
        catch (const std::exception& e) {
            std::cerr << "[Config::loadConfig()] Error loading " << key << ": " << e.what() << std::endl;
        }
    }
}