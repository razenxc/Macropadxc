#pragma once

#include <string>

namespace SystemUtils
{
    void mediaPrevious();
    void mediaPlayPause();
    void mediaNext();
    void volumeUp();
    void volumeDown();
    void volumeMute();
    void openUrl(const std::string& url);
    void runApplication(const std::string& path);

    std::string getExecutableDir();
}