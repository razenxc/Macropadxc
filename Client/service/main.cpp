#include <iostream>
#include <serial/serial.h>
#include <chrono>
#include <thread>

#include "SystemUtils.h"
#include "Config.h"
#include "Actions.h"

int main()
{
    std::string welcomeMessage = R"(
     __    __                 __                 _          
    / / /\ \ \__ _ _ __ ___  / _\ ___ _ ____   _(_) ___ ___ 
    \ \/  \/ / _` | '__/ _ \ \ \ / _ \ '__\ \ / / |/ __/ _ \
     \  /\  / (_| | | |  __/ _\ \  __/ |   \ V /| | (_|  __/
      \/  \/ \__,_|_|  \___| \__/\___|_|    \_/ |_|\___\___|
                                                        
    )";

    std::cout << welcomeMessage << std::endl;

    Config::init();
    Config::loadConfig();
    
    std::string port = "COM4";
    unsigned long baud = 115200;

    while (true)
    {
        serial::Serial mySerial;
    
        try
        {
            std::cout << "[Status][main()] Connecting to " << "port: " << port << " at speed: " << baud << " ..." << std::endl;

            mySerial.setPort(port);
            mySerial.setBaudrate(baud);
            auto timeout = serial::Timeout::simpleTimeout(1000);
            mySerial.setTimeout(timeout);
            mySerial.open();
        } 
        catch (serial::IOException& e) 
        {
            std::cerr << "[Error][main()] Connection failed! " << std::endl;
            std::cerr << "[Error][main()] Detalis: " << e.what() << std::endl;
            std::cerr << "[Error][main()] Retrying in 2s..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            continue;
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "[Error][main()] Invalid arguments (wrong baudrate or port)!" << std::endl;
            break;
        }

        std::cout << "[Status][main()] Connected!" << std::endl;
        
        while (mySerial.isOpen())
        {
            try
            {
                if (mySerial.available())
                {
                    std::string data = mySerial.readline().substr(0, 4);

                    std::cout << "[Status][main()] Received data: " << data << std::endl;

                    if (!data.empty())
                    {
                        Config::hotReload();
                        Actions::execute(data);
                    }
                }
            }
            catch (serial::SerialException& e)
            {
                std::cerr << "[Error][main()] Device disconnected!" << std::endl;
                break;
            }
            catch (serial::IOException& e)
            {
                std::cerr << "[Error][main()] IO Error during read!" << std::endl;
                break;
            }
        }
    }

    return 0;
}