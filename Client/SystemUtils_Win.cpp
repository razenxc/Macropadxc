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

    void runAppllicaton(const std::string& path)
    {
        ShellExecuteA(0, "open", path.c_str(), 0, 0, SW_SHOWNORMAL);
    }
}