#include "cl_utils.h"

#include <windows.h>
#include <tlhelp32.h>

bool isProcessRunning(const std::string& processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (_stricmp(entry.szExeFile, processName.c_str()) == 0)
            {
                exists = true;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }
    CloseHandle(snapshot);
    return exists;
}