set(MACROPADXC_CURRENT_VERSION 1.0.1)

# ======
# CMake
cmake_minimum_required(VERSION 3.10)
project(WareInteraction)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

# ==== GLAD ====
add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include")
if (UNIX AND NOT APPLE)
    target_link_libraries(glad ${CMAKE_DL_LIBS})
endif()

# ===== GLFW =====
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

# ==== IMGUI =====
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui")
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw)

# ===== Service & Client =====
add_subdirectory(service)
add_subdirectory(client)

# ======
# CPack
if (WIN32)
    set(USERVAR_INSTALL_PATH bin)
else()
    set(USERVAR_INSTALL_PATH /opt/Macropadxc)
endif()

install(TARGETS WareClient WareService DESTINATION ${USERVAR_INSTALL_PATH})

set(CPACK_PACKAGE_NAME "Macropadxc")
set(CPACK_PACKAGE_VENDOR "razenxc")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Macropadxc driver")
set(CPACK_PACKAGE_VERSION ${MACROPADXC_CURRENT_VERSION})

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    
    set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$DESKTOP\\\\Macropadxc.lnk' '$INSTDIR\\\\bin\\\\WareClient.exe'")
    
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
        WriteRegStr HKCU 'Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Run' 'MacropadxcService' '\\\"$INSTDIR/bin/WareService.exe\\\" --no-console'
        
        SetOutPath '$INSTDIR/bin'
        
        ExecWait 'icacls \\\"$INSTDIR\\\" /grant *S-1-5-32-545:(OI)(CI)M /T'
        
        ExecShell 'open' '$INSTDIR/bin/WareService.exe' '--no-console'
    ")
    
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
        DeleteRegValue HKCU 'Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Run' 'MacropadxcService'
        nsExec::ExecToLog 'taskkill /F /IM WareService.exe'
    ")
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")

    set(CPACK_DEBIAN_PACKAGE_NAME "macropadxc")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "razenxc")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "playerctl, pulseaudio-utils, xdg-utils, ydotool")
    
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/macropadxc.service"
    "[Unit]
    Description=Macropadxc Service (User Level)
    After=graphical-session.target

    [Service]
    Type=simple
    ExecStart=/opt/Macropadxc/WareService --no-console
    Restart=on-failure

    [Install]
    WantedBy=default.target
    ")

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/macropadxc.service" DESTINATION /usr/lib/systemd/user)

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/macropadxc.desktop"
    "[Desktop Entry]
    Version=1.0
    Type=Application
    Name=Macropadxc
    Comment=Macropadxc Configuration Client
    Exec=/opt/Macropadxc/WareClient
    Icon=wimacropad
    Terminal=false
    Categories=Utility;HardwareSettings;
    ")
    
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/macropadxc.desktop" DESTINATION /usr/share/applications)
    
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/postinst" 
    "#!/bin/sh
    chmod 777 /opt/Macropadxc

    systemctl --global daemon-reload
    systemctl --global enable macropadxc.service
    ")

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/prerm" 
    "#!/bin/sh
    systemctl --global disable macropadxc.service
    ")

    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/postinst")
endif()

include(CPack)