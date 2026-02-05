set(SHARED_SOURCES
    ../service/Config.cpp
)

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    list(APPEND SHARED_SOURCES ../service/SystemUtils_Win.cpp)
    add_definitions(-D_WIN32_WINNT=0x0600)
else()
    list(APPEND SHARED_SOURCES ../service/SystemUtils_Linux.cpp)
endif()

add_executable(WareClient main.cpp ${SHARED_SOURCES})

if(WIN32 OR MINGW OR MSYS OR CYGWIN)
    set_target_properties(WareClient PROPERTIES WIN32_EXECUTABLE ON)
endif()

target_include_directories(WareClient PRIVATE ../service)

target_link_libraries(WareClient 
    PRIVATE 
    imgui 
    glfw 
    nlohmann_json::nlohmann_json
)

if(WIN32)
    target_link_libraries(WareClient PRIVATE opengl32)
else()
    target_link_libraries(WareClient PRIVATE GL)
endif()