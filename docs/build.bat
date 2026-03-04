@echo off

REM Freddy Senamela
REM Personal Time Tracker
REM 12 November 2025

echo building object files...
g++ -std=c++20 -fmodules-ts -c ..\src\consoleEnhancer.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\utility.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\activity.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\timeSession.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\fileManager.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\reportGenerator.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\timeTracker.cpp
g++ -std=c++20 -fmodules-ts -c ..\src\main.cpp


echo building executable file...
g++ -std=c++20 -fmodules-ts consoleEnhancer.o utility.o activity.o timeSession.o fileManager.o reportGenerator.o timeTracker.o main.o -o ..\bin\main.exe

echo Cleaning up...
del *.o

echo.
echo Running Program...
echo ----------------------------------------------------------
..\bin\main.exe

echo ----------------------------------------------------------
echo program ran successfully

pause