#include <iostream>
#include <serial/serial.h>

#include "SystemUtils.h"
#include "Config.h"
#include "Utils.h"

int main()
{
    Config::Init();
    Config::Write(std::make_pair("P0F1", std::to_string(SystemUtils::Types::MEDIA_PREVIOUS)));
    Config::Write(std::make_pair("P0F2", std::to_string(SystemUtils::Types::MEDIA_PLAYPAUSE)));
    Config::Write(std::make_pair("P0F3", std::to_string(SystemUtils::Types::MEDIA_NEXT)));
    Config::Write(std::make_pair("P0F4", std::to_string(SystemUtils::Types::VOLUME_UP)));
    Config::Write(std::make_pair("P0F8", std::to_string(SystemUtils::Types::VOLUME_DOWN)));

    std::string port = "COM6";
    unsigned long baud = 115200;

    serial::Serial mySerial(port, baud, serial::Timeout::simpleTimeout(1000));

    
    std::cout << "Connecting to " << "port: " << port << " at speed: " << baud << " ..." << std::endl;
    try
    {
        mySerial.isOpen();
    } catch (serial::IOException& e) {
        std::cerr << "Failed to open port: " << port << std::endl;
        std::cerr << "Detalis: " << e.what() << std::endl;
        return -1;
    }

    std::vector<std::pair<std::string, std::string>> cfg = Config::Get();
    
    while (true)
    {
        if (mySerial.available())
        {
            std::string data = mySerial.readline();

            std::cout << "Received data: " << data << std::endl;

            for (auto &&i : cfg)
            {
                if (i.first == data.substr(0, 4))
                {
                    if (i.second == std::to_string(SystemUtils::Types::MEDIA_PREVIOUS))
                    {
                        std::cout << "Executing SystemUtils::mediaPrevious();" << std::endl;
                        SystemUtils::mediaPrevious();
                    }
                    else if (i.second == std::to_string(SystemUtils::Types::MEDIA_PLAYPAUSE))
                    {
                        std::cout << "Executing SystemUtils::mediaPlayPause();" << std::endl;
                        SystemUtils::mediaPlayPause();
                    }
                    else if (i.second == std::to_string(SystemUtils::Types::MEDIA_NEXT))
                    {
                        std::cout << "Executing SystemUtils::mediaNext();" << std::endl;
                        SystemUtils::mediaNext();
                    }
                    else if (i.second == std::to_string(SystemUtils::Types::VOLUME_UP))
                    {
                        std::cout << "Executing SystemUtils::volumeUp();" << std::endl;
                        SystemUtils::volumeUp();
                    }
                    else if (i.second == std::to_string(SystemUtils::Types::VOLUME_DOWN))
                    {
                        std::cout << "Executing SystemUtils::volumeDown();" << std::endl;
                        SystemUtils::volumeDown();
                    }
                }
            }
        }
    }

    return 0;
}