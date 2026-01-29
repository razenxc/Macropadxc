#include <iostream>
#include <serial/serial.h>
#include <chrono>
#include <thread>

#include "SystemUtils.h"
#include "Config.h"
#include "Utils.h"
#include "Actions.h"

int main()
{
    Config::init();
    // Config::loadConfig();
    std::string port = "/dev/ttyUSB0";
    unsigned long baud = 115200;

    while (true)
    {
        serial::Serial mySerial;
    
        try
        {
            std::cout << "Connecting to " << "port: " << port << " at speed: " << baud << " ..." << std::endl;

            mySerial.setPort(port);
            mySerial.setBaudrate(baud);
            auto timeout = serial::Timeout::simpleTimeout(1000);
            mySerial.setTimeout(timeout);
            mySerial.open();
        } 
        catch (serial::IOException& e) 
        {
            std::cerr << "Connection failed! " << std::endl;
            std::cerr << "Detalis: " << e.what() << std::endl;
            std::cerr << "Retrying in 2s..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            continue;
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Invalid arguments (wrong baudrate or port)!" << std::endl;
            break;
        }

        std::cout << "Connected!" << std::endl;
        
        while (mySerial.isOpen())
        {
            try
            {
                if (mySerial.available())
                {
                    std::string data = mySerial.readline().substr(0, 4);

                    std::cout << "Received data: " << data << std::endl;

                    if (!data.empty())
                    {
                        Actions::execute(data);
                    }
                }
            }
            catch (serial::SerialException& e)
            {
                std::cerr << "Device disconnected!" << std::endl;
                break;
            }
            catch (serial::IOException& e)
            {
                std::cerr << "IO Error during read!" << std::endl;
                break; 
            }
        }
    }

    return 0;
}