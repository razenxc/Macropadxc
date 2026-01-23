#pragma once

#include <string>
#include <vector>

namespace Config
{
    void Init();
    void Write(std::pair<std::string, std::string>);
    std::vector<std::pair<std::string, std::string>> Get();
}