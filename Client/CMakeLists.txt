cmake_minimum_required(VERSION 3.10)
project(WareInteraction)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static")

# ===== SERIAL LIBRARY =====
set(SERIAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/serial")

if(NOT EXISTS "${SERIAL_DIR}/include/serial/serial.h")
    message(FATAL_ERROR ">>> Serial submodule not found! Run: git submodule update --init --recursive <<<")
endif()

set(SERIAL_SRCS
    ${SERIAL_DIR}/src/serial.cc
)

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    list(APPEND SERIAL_SRCS
        ${SERIAL_DIR}/src/impl/win.cc
        ${SERIAL_DIR}/src/impl/list_ports/list_ports_win.cc
    )
else()
    list(APPEND SERIAL_SRCS
        ${SERIAL_DIR}/src/impl/unix.cc
        ${SERIAL_DIR}/src/impl/list_ports/list_ports_linux.cc
    )
endif()

add_library(serial_lib STATIC ${SERIAL_SRCS})
target_include_directories(serial_lib PUBLIC ${SERIAL_DIR}/include)

if(NOT (WIN32 OR MINGW OR MSYS OR CYGWIN))
    target_link_libraries(serial_lib rt pthread)
endif()

# ===== JSON LIBRARY =====
set(JSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json")

if(NOT EXISTS "${JSON_DIR}/include/nlohmann/json.hpp")
    message(FATAL_ERROR ">>> Json submodule not found! Run: git submodule update --init --recursive <<<")
endif()

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${JSON_DIR})

# ===== CLIENT =====
add_subdirectory(src)