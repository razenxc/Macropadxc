#include "sv_utils.h"

#include <unistd.h>
#include <limits.h>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace SystemUtils
{
    void run(std::string cmd)
    {
        std::string finalCmd = cmd + " > /dev/null 2>&1 &";
        system(finalCmd.c_str());
    }
    
    void mediaPrevious()
    {
        run("playerctl previous");
    }

    void mediaPlayPause()
    {
        run("playerctl play-pause");
    }

    void mediaNext()
    {
        run("playerctl next");
    }

    void volumeUp()
    {
        run("pactl set-sink-volume @DEFAULT_SINK@ +5%");
    }

    void volumeDown()
    {
        run("pactl set-sink-volume @DEFAULT_SINK@ -5%");
    }

    void volumeMute()
    {
        run("pactl set-sink-mute @DEFAULT_SINK@ toggle");
    }

    void openUrl(const std::string& url)
    {
        std::string cmd = "xdg-open " + url;
        run(cmd.c_str());
    }

    void runApplication(const std::string& path)
    {
        if (path.empty()) return;
        std::string cmd = "\"" + path + "\" &";
        int ret = system(cmd.c_str());
        (void)ret;
    }

    // Helper function for simulateKeystrokes
    std::string mapKeyToYdotool(std::string key) 
    {
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        for(auto& c : key) c = toupper(c);

        static const std::map<std::string, std::string> keyDictionary = {
            // System and modifiers
            {"ESC", "esc"}, {"ESCAPE", "esc"},
            {"CONTROL", "ctrl"}, {"CTRL", "ctrl"}, {"LCTRL", "leftctrl"}, {"RCTRL", "rightctrl"},
            {"SHIFT", "shift"}, {"LSHIFT", "leftshift"}, {"RSHIFT", "rightshift"},
            {"ALT", "alt"}, {"LALT", "leftalt"}, {"RALT", "rightalt"},
            {"WIN", "super"}, {"SUPER", "super"}, {"META", "super"},
            {"ENTER", "enter"}, {"RETURN", "enter"}, {"TAB", "tab"}, {"SPACE", "space"}, {"BACKSPACE", "backspace"},
            {"CAPSLOCK", "capslock"}, {"APPS", "menu"},

            // Navigation
            {"UP", "up"}, {"DOWN", "down"}, {"LEFT", "left"}, {"RIGHT", "right"},
            {"INSERT", "insert"}, {"DELETE", "delete"}, {"DEL", "delete"},
            {"HOME", "home"}, {"END", "end"}, {"PAGEUP", "pageup"}, {"PAGEDOWN", "pagedown"},
            {"PRINTSCREEN", "sysrq"}, {"PRTSC", "sysrq"}, {"SCROLLLOCK", "scrolllock"}, {"PAUSE", "pause"},

            // Function keys
            {"F1", "f1"}, {"F2", "f2"}, {"F3", "f3"}, {"F4", "f4"},
            {"F5", "f5"}, {"F6", "f6"}, {"F7", "f7"}, {"F8", "f8"},
            {"F9", "f9"}, {"F10", "f10"}, {"F11", "f11"}, {"F12", "f12"},
            {"F13", "f13"}, {"F14", "f14"}, {"F15", "f15"}, {"F16", "f16"},
            {"F17", "f17"}, {"F18", "f18"}, {"F19", "f19"}, {"F20", "f20"},
            {"F21", "f21"}, {"F22", "f22"}, {"F23", "f23"}, {"F24", "f24"},

            // Numpad
            {"NUM0", "kp0"}, {"NUM1", "kp1"}, {"NUM2", "kp2"}, {"NUM3", "kp3"},
            {"NUM4", "kp4"}, {"NUM5", "kp5"}, {"NUM6", "kp6"}, {"NUM7", "kp7"},
            {"NUM8", "kp8"}, {"NUM9", "kp9"},
            {"NUMMULTIPLY", "kpasterisk"}, 
            {"NUMADD", "kpplus"},          
            {"NUMSUBTRACT", "kpminus"}, 
            {"NUMDECIMAL", "kpdot"},   
            {"NUMDIVIDE", "kpslash"},     
            {"NUMLOCK", "numlock"},

            // Punctuation marks
            {";", "semicolon"}, {":", "semicolon"},
            {"+", "equal"}, {"=", "equal"},
            {",", "comma"}, {"<", "comma"},
            {"-", "minus"}, {"_", "minus"},
            {".", "dot"}, {">", "dot"},
            {"/", "slash"}, {"?", "slash"},
            {"~", "grave"}, {"`", "grave"},
            {"[", "leftbrace"}, {"{", "leftbrace"},
            {"\\", "backslash"}, {"|", "backslash"},
            {"]", "rightbrace"}, {"}", "rightbrace"},
            {"'", "apostrophe"}, {"\"", "apostrophe"}
        };

        auto it = keyDictionary.find(key);
        if (it != keyDictionary.end())
        {
            return it->second;
        }

        if (key.length() == 1) 
        {
            char c = key[0];
            if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
            {
                std::string res(1, tolower(c));
                return res;
            }
        }

        return "";
    }

    void simulateKeystrokes(const std::string& keysCombo) 
    {
        if (keysCombo.empty()) return;

        std::stringstream ss(keysCombo);
        std::string token;
        std::string ydotool_combo = "";

        while (std::getline(ss, token, '+')) 
        {
            if (!ydotool_combo.empty()) 
            {
                ydotool_combo += "+"; 
            }
            ydotool_combo += mapKeyToYdotool(token);
        }

        if (!ydotool_combo.empty()) 
        {
            std::string cmd = "ydotool key " + ydotool_combo;
            int ret = system(cmd.c_str());
            (void)ret;
        }
    }

    // Misc
    std::string getExecutableDir()
    {
        char result[PATH_MAX];

        size_t count = readlink("/proc/self/exe", result, PATH_MAX);
        
        if (count != -1) 
        {
            std::string path(result, count);
            size_t lastSlash = path.find_last_of('/');
            if (lastSlash != std::string::npos) 
            {
                return path.substr(0, lastSlash);
            }
        }
        return "";
    }
}