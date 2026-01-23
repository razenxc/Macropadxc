cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(WareInteraction)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include(FetchContent)

FetchContent_Declare(
  serial_lib
  GIT_REPOSITORY https://github.com/wjwwood/serial.git
  GIT_TAG        main
  PATCH_COMMAND  ${CMAKE_COMMAND} -E copy
                 ${CMAKE_CURRENT_SOURCE_DIR}/SerialClean.cmake
                 <SOURCE_DIR>/CMakeLists.txt
)

FetchContent_MakeAvailable(serial_lib)

if(WIN32 OR MINGW OR MSYS OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    set(PLATFORM_SOURCES SystemUtils_Win.cpp)
    add_definitions(-D_WIN32_WINNT=0x0600)
else()
    set(PLATFORM_SOURCES SystemUtils_Linux.cpp)
endif()

add_executable(WareInteractionClient main.cpp SystemUtils.h Config.h Config.cpp Utils.h Utils.cpp ${PLATFORM_SOURCES})
target_link_libraries(WareInteractionClient PRIVATE serial)