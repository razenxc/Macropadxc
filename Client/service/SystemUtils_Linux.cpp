#include "SystemUtils.h"

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
    }

    void volumeDown()
    {
    }

    void volumeMute()
    {
    }

    void openUrl(const std::string& url)
    {
        std::string cmd = "xdg-open " + url;
        run(cmd.c_str());
    }

    void runApplication(const std::string& path)
    {
    }

    std::string getExecutableDir()
    {
    }
}