#include "sv_utils.h"

#include <windows.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

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

        static const std::map<std::string, WORD> keyDictionary = {
            // System and modifiers
            {"ESC", VK_ESCAPE},
            {"CONTROL", VK_CONTROL}, {"CTRL", VK_CONTROL}, {"LCTRL", VK_LCONTROL}, {"RCTRL", VK_RCONTROL},
            {"SHIFT", VK_SHIFT}, {"LSHIFT", VK_LSHIFT}, {"RSHIFT", VK_RSHIFT},
            {"ALT", VK_MENU}, {"LALT", VK_LMENU}, {"RALT", VK_RMENU},
            {"WIN", VK_LWIN}, {"SUPER", VK_LWIN}, {"META", VK_LWIN}, {"RWIN", VK_RWIN}, // Аліаси для Win
            {"ENTER", VK_RETURN}, {"TAB", VK_TAB}, {"SPACE", VK_SPACE}, {"BACKSPACE", VK_BACK},
            {"CAPSLOCK", VK_CAPITAL}, {"APPS", VK_APPS}, // APPS - це кнопка "Меню" біля правого Ctrl

            // Navigation
            {"UP", VK_UP}, {"DOWN", VK_DOWN}, {"LEFT", VK_LEFT}, {"RIGHT", VK_RIGHT},
            {"INSERT", VK_INSERT}, {"DELETE", VK_DELETE}, {"DEL", VK_DELETE},
            {"HOME", VK_HOME}, {"END", VK_END}, {"PAGEUP", VK_PRIOR}, {"PAGEDOWN", VK_NEXT},
            {"PRINTSCREEN", VK_SNAPSHOT}, {"PRTSC", VK_SNAPSHOT}, {"SCROLLLOCK", VK_SCROLL}, {"PAUSE", VK_PAUSE},

            // Function keys
            {"F1", VK_F1}, {"F2", VK_F2}, {"F3", VK_F3}, {"F4", VK_F4},
            {"F5", VK_F5}, {"F6", VK_F6}, {"F7", VK_F7}, {"F8", VK_F8},
            {"F9", VK_F9}, {"F10", VK_F10}, {"F11", VK_F11}, {"F12", VK_F12},
            {"F13", VK_F13}, {"F14", VK_F14}, {"F15", VK_F15}, {"F16", VK_F16},
            {"F17", VK_F17}, {"F18", VK_F18}, {"F19", VK_F19}, {"F20", VK_F20},
            {"F21", VK_F21}, {"F22", VK_F22}, {"F23", VK_F23}, {"F24", VK_F24},

            // Numpad
            {"NUM0", VK_NUMPAD0}, {"NUM1", VK_NUMPAD1}, {"NUM2", VK_NUMPAD2}, {"NUM3", VK_NUMPAD3},
            {"NUM4", VK_NUMPAD4}, {"NUM5", VK_NUMPAD5}, {"NUM6", VK_NUMPAD6}, {"NUM7", VK_NUMPAD7},
            {"NUM8", VK_NUMPAD8}, {"NUM9", VK_NUMPAD9},
            {"NUMMULTIPLY", VK_MULTIPLY}, // Numpad *
            {"NUMADD", VK_ADD},           // Numpad +
            {"NUMSUBTRACT", VK_SUBTRACT}, // Numpad -
            {"NUMDECIMAL", VK_DECIMAL},   // Numpad .
            {"NUMDIVIDE", VK_DIVIDE},     // Numpad /
            {"NUMLOCK", VK_NUMLOCK},

            // Punctuation marks
            {";", VK_OEM_1}, {":", VK_OEM_1},
            {"+", VK_OEM_PLUS}, {"=", VK_OEM_PLUS},
            {",", VK_OEM_COMMA}, {"<", VK_OEM_COMMA},
            {"-", VK_OEM_MINUS}, {"_", VK_OEM_MINUS},
            {".", VK_OEM_PERIOD}, {">", VK_OEM_PERIOD},
            {"/", VK_OEM_2}, {"?", VK_OEM_2},
            {"~", VK_OEM_3}, {"`", VK_OEM_3},
            {"[", VK_OEM_4}, {"{", VK_OEM_4},
            {"\\", VK_OEM_5}, {"|", VK_OEM_5},
            {"]", VK_OEM_6}, {"}", VK_OEM_6},
            {"'", VK_OEM_7}, {"\"", VK_OEM_7}
        };

        auto it = keyDictionary.find(key);

        if (it != keyDictionary.end())
        {
            return it->second;
        }

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