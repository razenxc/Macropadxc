cmake_minimum_required(VERSION 3.10)
project(serial_clean)

if(WIN32 OR MINGW OR MSYS OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    message(STATUS ">>> SERIAL LIBRARY: Detected MSYS/MinGW - Forcing Windows Mode <<<")
    
    set(SERIAL_IMPL src/impl/win.cc)
    add_definitions(-D_WIN32)
    add_definitions(-D__MINGW32__)
    link_libraries(setupapi) 
    
else()
    message(STATUS ">>> SERIAL LIBRARY: Unix mode <<<")
    set(SERIAL_IMPL src/impl/unix.cc)
endif()

add_library(serial STATIC
    src/serial.cc
    ${SERIAL_IMPL}
)

target_include_directories(serial PUBLIC include)

if(UNIX AND NOT (WIN32 OR MINGW OR MSYS))
    target_link_libraries(serial rt pthread)
endif()