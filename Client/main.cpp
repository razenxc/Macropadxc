#include <iostream>
#include <serial/serial.h>

#include "SystemUtils.h"

int main()
{
    std::string port = "COM5";
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

    while (true)
    {
        if (mySerial.available())
        {
            std::string data = mySerial.readline();

            std::cout << data << std::endl;
            if (data[3] == '1')
            {
                std::cout << "SystemUtils::mediaPlayPause();" << std::endl;
                SystemUtils::mediaPlayPause();
            }
        }
    }

    return 0;
}