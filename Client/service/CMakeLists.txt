set(THE_SOURCES
    main.cpp 
    SystemUtils.h 
    Config.h Config.cpp
    Actions.h Actions.cpp
)

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    list(APPEND THE_SOURCES SystemUtils_Win.cpp)
    add_definitions(-D_WIN32_WINNT=0x0600)
else()
    list(APPEND THE_SOURCES SystemUtils_Linux.cpp)
endif()

add_executable(WareService ${THE_SOURCES})

target_include_directories(WareService PRIVATE .)
target_link_libraries(WareService PRIVATE serial_lib)
target_link_libraries(WareService PRIVATE nlohmann_json::nlohmann_json)