cmake_minimum_required(VERSION 3.10)

project(Cluster LANGUAGES CXX)
message("CMAKE_SYSROOT " ${CMAKE_SYSROOT})
message("CMAKE_LIBRARY_ARCHITECTURE " ${CMAKE_LIBRARY_ARCHITECTURE})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(zenohc_DIR "/usr/local/lib/cmake/zenohc")
set(zenohcxx_DIR "/usr/local/lib/cmake/zenohcxx")
find_package(Qt6 COMPONENTS Core Quick DBus SerialBus REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-rpath-link, ${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} -L${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} -L${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
# Enable automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt_add_resources(QT_RESOURCES ./src/resources.qrc)

add_executable(speedometer ${QT_RESOURCES} 
    ./src/main.cpp
    ./src/CANBusHandler.cpp
    ./include/CANBusHandler.hpp
)

target_link_libraries(speedometer zenohcxx::zenohc -lm -ldl Qt6::Core Qt6::DBus Qt6::Quick Qt6::SerialBus)

add_executable(zenoh
    ./middelWare/src/main.cpp
)

target_link_libraries(zenoh PRIVATE zenohcxx::zenohc)
