set(THE_SOURCES
    main.cpp 
    sv_utils.h 
    config.h config.cpp
    actions.h actions.cpp
)

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    list(APPEND THE_SOURCES sv_utils_win.cpp)
    add_definitions(-D_WIN32_WINNT=0x0600)
else()
    list(APPEND THE_SOURCES sv_utils_linux.cpp)
endif()

add_executable(MacropadxcService ${THE_SOURCES})

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    target_link_libraries(MacropadxcService PRIVATE setupapi)
endif()

target_link_options(MacropadxcService PRIVATE "-static")

target_include_directories(MacropadxcService PRIVATE .)
target_link_libraries(MacropadxcService PRIVATE serial_lib)
target_link_libraries(MacropadxcService PRIVATE nlohmann_json::nlohmann_json)