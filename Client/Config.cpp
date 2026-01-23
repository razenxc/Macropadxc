#include "Config.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace Config 
{
    void Init()
    {
        std::string cfgFileName = "config.wcfg";

        if (std::filesystem::is_regular_file(cfgFileName))
        {
            return;
        }

        std::ofstream cfg;
        cfg.open(cfgFileName);

        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 1; j < 9; j++)
            {
                cfg << "P" << i << "F" << j << "|" << '\n';
            }
            
        }
        
        cfg.close();
    }

    void Write(std::pair<std::string, std::string> keyvalue)
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

    std::vector<std::pair<std::string, std::string>> Get()
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
}