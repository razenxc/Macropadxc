#pragma once

#include <string>

namespace Actions
{
    void execute(const std::string& buttonCode);
}

enum ActionType 
{
    CMD_NONE,
    CMD_MEDIA_PREV,
    CMD_MEDIA_PLAY_PAUSE,
    CMD_MEDIA_NEXT,
    CMD_VOLUME_UP,
    CMD_VOLUME_DOWN,
    CMD_VOLUME_MUTE,
    CMD_OPEN_URL,
    CMD_RUN_APP
};

struct Action
{
    ActionType type;
    std::string payload;
};