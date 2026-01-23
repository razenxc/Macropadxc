#pragma once

#include <string>

namespace SystemUtils
{
    void mediaPrevious();
    void mediaPlayPause();
    void mediaNext();
    void openBrowser(const std::string& url);

    enum Types
    {
        MEDIA_PREVIOUS,
        MEDIA_PLAYPAUSE,
        MEDIA_NEXT,
        OPEN_BROWSER
    };
}