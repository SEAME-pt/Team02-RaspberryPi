cmake_minimum_required(VERSION 3.10)

# Project Name
project(publisher)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

# Enable automatic moc processing
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)

# Add source files for the project
set(SOURCE_FILES
    lanes_publisher.cpp
)

# Add the executable target
add_executable(publisher ${SOURCE_FILES})

# Include and Link Directories
include_directories(/usr/local/include)  # Ensure this path is correct
link_directories(/usr/local/lib)  # Ensure the Zenoh library is in this directory

# Define Preprocessor Macros for Zenoh
target_compile_definitions(publisher PRIVATE ZENOHCXX_ZENOHC)

# Add QML resources if you're using QML
qt5_add_resources(publisher "ui/resources.qrc")

# Link with Qt5 and Zenoh
target_link_libraries(publisher Qt5::Core Qt5::Quick zenohc)