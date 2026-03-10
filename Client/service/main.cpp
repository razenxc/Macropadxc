#include <iostream>
#include <serial/serial.h>
#include <chrono>
#include <thread>

#include "SystemUtils.h"
#include "Config.h"
#include "Actions.h"

std::string autoDetectPort()
{
    std::cout << "[Status][autoDetectPort()] Scanning ports..." << std::endl;
    
    std::vector<serial::PortInfo> devices = serial::list_ports();
    std::vector<serial::PortInfo>::iterator it = devices.begin();

    while (it != devices.end())
    {
        serial::PortInfo device = *it++;
        std::string port = device.port;

        std::cout << "[Status][autoDetectPort()] Checking " << port  << "... " << std::endl;

        try
        {
            serial::Serial mySerial(port, 115200, serial::Timeout::simpleTimeout(1000));

            if (mySerial.isOpen())
            {
                // Waiting due to controller DTR reset
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                mySerial.flushInput();
                mySerial.write("WAREI_HEY\n");

                std::string data = mySerial.read(50);

                if (data.find("WAREI_OK") != std::string::npos)
                {
                    std::cout << "[Status][autoDetectPort()] Found!" << std::endl;
                    return port;
                }
                else
                {
                    std::cout << "[Status][autoDetectPort()] Port not found. Trying the next one." << std::endl;
                }

                mySerial.close();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    return "";
}

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
    
    std::string port = "";
    unsigned long baud = 115200;
    serial::Serial mySerial;

    while (true)
    {
        try
        {
            if (!mySerial.isOpen())
            {
                port = autoDetectPort();
                if (port == "") 
                {
                        std::cout << "[Status][main()] Device not found. Retrying in 3s..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        continue;
                    }
            }

            std::cout << "[Status][main()] Connecting to " << "port: " << port << " at speed: " << baud << " ..." << std::endl;

            mySerial.setPort(port);
            mySerial.setBaudrate(baud);
            auto timeout = serial::Timeout::simpleTimeout(1000);
            mySerial.setTimeout(timeout);
            mySerial.open();

            // waiting due to controller DTR reset
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "[Status][main()] Connected successfully!" << std::endl;
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
                    std::string data = mySerial.readline();

                    if (data.length() >= 2)
                    {
                        data = data.substr(0, 2);
                        std::cout << "[Status][main()] Received data: " << data << std::endl;
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
            catch (const std::exception& e) 
            {
                std::cerr << "[Error][main()] Exception: " << e.what() << std::endl;
            }
            catch (...) 
            {
                std::cerr << "[Error][main()] Unknown error!" << std::endl;
            }
        }
    }

    return 0;
}