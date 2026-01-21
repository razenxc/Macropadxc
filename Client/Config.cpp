#include "Config.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace Config 
{
    void Init()
    {
        std::ofstream cfg;
        cfg.open("config.wcfg");

        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {
                cfg << "P" << i << "F" << j << "|" << '\n';
            }
            
        }
        
        cfg.close();
    }

    void Write(std::pair<std::string, std::string> keyvalue)
    {
        std::ofstream cfg;
        cfg.open("config.wcfg");

        std::string line;

        while (std::getline(cfg, line)) {
            std::vector<std::string> data = Utils::Split(line);
            if (data[0] == keyvalue.first)
            {

            }
         }
    }
}