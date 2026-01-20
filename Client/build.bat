RMDIR /S /Q build 
MKDIR build 
CP "dlls/msys-2.0.dll" "build/msys-2.0.dll"
CD build 
cmake .. 
cmake --build .