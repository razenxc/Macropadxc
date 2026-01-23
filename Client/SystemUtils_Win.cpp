#include "SystemUtils.h"

#include <windows.h>

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
    
    void openBrowser(const std::string& url)
    {
        ShellExecuteA(0, "open", url.c_str(), 0, 0, SW_SHOWNORMAL);
    }

    void volumeUp()
    {
        keybd_event(VK_VOLUME_UP, 0, 0, 0);
    }

    void volumeDown()
    {
        keybd_event(VK_VOLUME_DOWN, 0, 0, 0);
    }
}