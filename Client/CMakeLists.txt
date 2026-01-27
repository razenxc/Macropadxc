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

add_subdirectory(src)