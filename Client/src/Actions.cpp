#include "Actions.h"
#include "Config.h"
#include "SystemUtils.h"

#include <iostream>

namespace Actions
{
    void execute(const std::string& buttonCode)
    {
        if (Config::keyBindings.find(buttonCode) == Config::keyBindings.end())
        {
            std::cout << "Actions > Unbound button: " << buttonCode << std::endl;
            return;
        }

        Action action = Config::keyBindings[buttonCode];

        switch (action.type)
        {
            case CMD_NONE:
                break;
            case CMD_MEDIA_PREV:
                SystemUtils::mediaPrevious();
                std::cout << "Actions > Executed SystemUtils::mediaPrevious();" << std::endl;
                break;
            case CMD_MEDIA_PLAY_PAUSE:
                SystemUtils::mediaPlayPause();
                std::cout << "Actions > Executed SystemUtils::mediaPlayPause();" << std::endl;
                break;
            case CMD_MEDIA_NEXT:
                SystemUtils::mediaNext();
                std::cout << "Actions > Executed SystemUtils::mediaNext();" << std::endl;
                break;
            case CMD_VOLUME_UP:
                SystemUtils::volumeUp();
                std::cout << "Actions > Executed SystemUtils::volumeUp();" << std::endl;
                break;
            case CMD_VOLUME_DOWN:
                SystemUtils::volumeDown();
                std::cout << "Actions > Executed SystemUtils::volumeDown();" << std::endl;
                break;
            case CMD_VOLUME_MUTE:
                SystemUtils::volumeMute();
                std::cout << "Actions > Executed SystemUtils::volumeMute();" << std::endl;
                break;
            case CMD_OPEN_URL:
                SystemUtils::openUrl(action.payload);
                std::cout << "Actions > Executed SystemUtils::openUrl(action.payload);" << "Payload: " << action.payload << std::endl;
                break;
            case CMD_RUN_APP:
                SystemUtils::runApplication(action.payload);
                std::cout << "Actions > Executed SystemUtils::runAppllicaton(action.payload);" << "Payload: " << action.payload << std::endl;
                break;
        }
    }
}