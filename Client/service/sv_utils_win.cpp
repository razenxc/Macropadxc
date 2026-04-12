#include "sv_utils.h"

#include <windows.h>
#include <vector>
#include <sstream>
#include <algorithm>

namespace SystemUtils
{
    void mediaPrevious()
    {
        keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
    }

    void mediaPlayPause()
    {
        keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);
    }

    void mediaNext()
    {
        keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
    }

    void volumeUp()
    {
        keybd_event(VK_VOLUME_UP, 0, 0, 0);
    }

    void volumeDown()
    {
        keybd_event(VK_VOLUME_DOWN, 0, 0, 0);
    }

    void volumeMute()
    {
        keybd_event(VK_VOLUME_MUTE, 0, 0, 0);
    }

    void openUrl(const std::string& url)
    {
        ShellExecuteA(0, "open", url.c_str(), 0, 0, SW_SHOWNORMAL);
    }

    void runApplication(const std::string& path)
    {
        ShellExecuteA(0, "open", path.c_str(), 0, 0, SW_SHOWNORMAL);
    }

    // Helper function for simulateKeystrokes
    WORD stringToVK(std::string key) 
    {
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        
        for(auto& c : key) c = toupper(c);

        if(key == "CTRL" || key == "CONTROL") return VK_CONTROL;
        if(key == "SHIFT") return VK_SHIFT;
        if(key == "ALT") return VK_MENU;
        if(key == "WIN" || key == "META") return VK_LWIN;
        if(key == "ENTER") return VK_RETURN;
        if(key == "TAB") return VK_TAB;
        if(key == "ESC" || key == "ESCAPE") return VK_ESCAPE;
        if(key == "SPACE") return VK_SPACE;
        if(key == "UP") return VK_UP;
        if(key == "DOWN") return VK_DOWN;
        if(key == "LEFT") return VK_LEFT;
        if(key == "RIGHT") return VK_RIGHT;

        if(key.length() == 1) 
        {
            char c = key[0];
            if((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
            {
                return c;
            }
        }
        return 0;
    }
    
    void simulateKeystrokes(const std::string& keysCombo)
    {
        if (keysCombo.empty()) return;

        std::vector<WORD> vks;
        std::stringstream ss(keysCombo);
        std::string token;

        while (std::getline(ss, token, '+')) 
        {
            WORD vk = stringToVK(token);
            if (vk != 0) vks.push_back(vk);
        }

        if (vks.empty()) return;

        std::vector<INPUT> inputs;

        for (WORD vk : vks) 
        {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = vk;
            inputs.push_back(input);
        }

        for (auto it = vks.rbegin(); it != vks.rend(); ++it) 
        {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = *it;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            inputs.push_back(input);
        }

        SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
    }

    // Misc
    std::string getExecutableDir()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);

        std::string fullPath(buffer);
        size_t lastSlash = fullPath.find_last_of("\\/");
        
        if (std::string::npos != lastSlash)
        {
            return fullPath.substr(0, lastSlash);
        }
        
        return "";
    }
}