#include <iostream>
#include <serial/serial.h>
#include <chrono>
#include <thread>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "sv_utils.h"
#include "config.h"
#include "actions.h"

bool autoDetectPort(serial::Serial& mySerial, unsigned long baud)
{
    std::cout << "[Status][autoDetectPort()] Scanning ports..." << std::endl;
    
    std::vector<serial::PortInfo> devices = serial::list_ports();
    std::vector<serial::PortInfo>::iterator it = devices.begin();

    while (it != devices.end())
    {
        serial::PortInfo device = *it++;
        std::string port = device.port;

        std::cout << "[Status][autoDetectPort()] Checking " << port << "... " << std::endl;

        try
        {
            mySerial.setPort(port);
            mySerial.setBaudrate(baud);
            auto timeout = serial::Timeout::simpleTimeout(1000);
            mySerial.setTimeout(timeout);
            mySerial.open();

            if (mySerial.isOpen())
            {
                mySerial.setDTR();  
                mySerial.setRTS();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                mySerial.flushInput();
                mySerial.write("WAREI_HEY\n");

                std::string data = mySerial.readline(50, "\n");

                if (data.find("WAREI_OK") != std::string::npos)
                {
                    std::cout << "[Status][autoDetectPort()] Found!" << std::endl;
                    return true;
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
            if (mySerial.isOpen()) mySerial.close();
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    bool noConsole = false;

    for (int i = 1; i < argc; i++) 
    {
        if (std::string(argv[i]) == "--no-console") 
        {
            noConsole = true;
            break;
        }
    }

    if (noConsole) 
    {
        #ifdef _WIN32
            HWND hwnd = GetConsoleWindow();
            if (hwnd) ShowWindow(hwnd, SW_HIDE);
        #endif
    }


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
    
    unsigned long baud = 115200;
    serial::Serial mySerial;

    while (true)
    {
        try
        {
            if (!mySerial.isOpen())
            {
                if (!autoDetectPort(mySerial, baud)) 
                {
                        std::cout << "[Status][main()] Device not found. Retrying in 3s..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        continue;
                }

                std::cout << "[Status][main()] Connected successfully!" << std::endl;
            }
                
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
            else 
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Prevent CPU load
            }
        } 
        catch (serial::SerialException& e)
        {
            std::cerr << "[Error][main()] Device disconnected!" << std::endl;
            if (mySerial.isOpen()) mySerial.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch (serial::IOException& e)
        {
            std::cerr << "[Error][main()] IO Error (cable unplugged?)!" << std::endl;
            if (mySerial.isOpen()) mySerial.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch (const std::exception& e) 
        {
            std::cerr << "[Error][main()] Exception: " << e.what() << std::endl;
            if (mySerial.isOpen()) mySerial.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch (...) 
        {
            std::cerr << "[Error][main()] Unknown error!" << std::endl;
            if (mySerial.isOpen()) mySerial.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}