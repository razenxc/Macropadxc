#pragma once

#include <string>

namespace Config
{
    void Init();
    void Write(std::pair<std::string, std::string>);
}