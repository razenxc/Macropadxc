if(WIN32 OR MINGW OR MSYS OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    set(PLATFORM_SOURCES SystemUtils_Win.cpp)
    add_definitions(-D_WIN32_WINNT=0x0600)
else()
    set(PLATFORM_SOURCES SystemUtils_Linux.cpp)
endif()

add_executable(WareInteractionClient 
main.cpp 
SystemUtils.h 
Config.h Config.cpp 
Utils.h Utils.cpp 
Actions.h Actions.cpp 
${PLATFORM_SOURCES})

target_include_directories(WareInteractionClient PRIVATE .)
target_link_libraries(WareInteractionClient PRIVATE serial)