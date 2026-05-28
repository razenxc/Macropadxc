#include "cl_utils.h"

#include <cstdlib>
    
bool isProcessRunning(const std::string& processName)
{
    std::string cmd = "pgrep -f " + processName + " > /dev/null 2>&1";
    return system(cmd.c_str()) == 0;
}