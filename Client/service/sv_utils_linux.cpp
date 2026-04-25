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
        
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        if (key == "win" || key == "meta" || key == "super") return "super";
        if (key == "esc" || key == "escape") return "esc";
        if (key == "enter" || key == "return") return "enter";
        if (key == "up") return "up";
        if (key == "down") return "down";
        if (key == "left") return "left";
        if (key == "right") return "right";
        if (key == "space") return "space";
        if (key == "alt") return "alt";
        if (key == "ctrl" || key == "control") return "ctrl";
        if (key == "shift") return "shift";
        
        return key;
    }

    void simulateKeystrokes(const std::string& keysCombo) 
    {
        if (keysCombo.empty()) return;

        std::stringstream ss(keysCombo);
        std::string token;
        std::string ydotool_combo = "";

        while (std::getline(ss, token, '+')) 
        {
            if (!ydotool_combo.empty()) {
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

        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        
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