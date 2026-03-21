cmake_minimum_required(VERSION 3.16)

project(ProductivityTracker VERSION 1.0 LANGUAGES CXX)

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt auto-tools (needed for signals/slots and .ui files)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt setup
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Backend source files (pure C++ logic, no Qt)
set(BACKEND_SOURCES
    backend/utility.h
    backend/utility.cpp
    backend/activity.h
    backend/activity.cpp
    backend/timeSession.h
    backend/timeSession.cpp
    backend/fileManager.h
    backend/fileManager.cpp
    backend/reportGenerator.h
    backend/reportGenerator.cpp
    backend/timeTracker.cpp
    backend/timeTracker.h
)

# GUI source files
set(GUI_SOURCES
    gui/main.cpp
    gui/mainwindow.cpp
    gui/mainwindow.h
)

# UI designer files
set(UI_FILES
    gui/mainwindow.ui
)

# Create the executable
qt_add_executable(ProductivityTracker
    ${BACKEND_SOURCES}
    ${GUI_SOURCES}
    ${UI_FILES}
)

# Enable C++20 modules for GCC
target_compile_options(ProductivityTracker PRIVATE -fmodules-ts)

# Tell the compiler where to find header files
target_include_directories(ProductivityTracker PRIVATE
    backend
    gui
)

# Link Qt libraries
target_link_libraries(ProductivityTracker PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# No console window on Windows
set_target_properties(ProductivityTracker PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ProductivityTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
