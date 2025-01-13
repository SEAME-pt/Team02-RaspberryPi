cmake_minimum_required(VERSION 3.10)

project(Cluster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(zenohc_DIR "/usr/local/lib/cmake/zenohc")
set(zenohcxx_DIR "/usr/local/lib/cmake/zenohcxx")

find_package(Qt6 COMPONENTS Core Quick DBus REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

# Enable Qt's Automatic MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add Resource File (QML and Other Resources)
qt_add_resources(QT_RESOURCES ./ui/resources.qrc)

# Define Executable Target
add_executable(speedometer
    ${QT_RESOURCES}       # Add Resource File
    ./src/main.cpp        # Main C++ File
    ./src/CANBusHandler.cpp # CANBusHandler Implementation
    ./include/CANBusHandler.hpp # CANBusHandler Header
)

target_link_libraries(speedometer zenohcxx::zenohc -lm -ldl Qt6::Core Qt6::DBus Qt6::Quick)

