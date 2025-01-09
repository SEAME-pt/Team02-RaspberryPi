cmake_minimum_required(VERSION 3.5)

# Project Name and Language
project(Speedometer LANGUAGES CXX)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Required Qt Modules
find_package(Qt6 COMPONENTS Core Quick SerialBus REQUIRED)

# Enable Qt's Automatic MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add Resource File (QML and Other Resources)
qt_add_resources(QT_RESOURCES ./src/resources.qrc)

# Define Executable Target
add_executable(speedometer
    ${QT_RESOURCES}       # Add Resource File
    ./src/main.cpp        # Main C++ File
    ./src/CANBusHandler.cpp # CANBusHandler Implementation
    ./include/CANBusHandler.hpp # CANBusHandler Header
)

# Link Qt Libraries
target_link_libraries(speedometer PRIVATE Qt6::Core Qt6::Quick Qt6::SerialBus)
