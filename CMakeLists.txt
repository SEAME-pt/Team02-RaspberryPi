cmake_minimum_required(VERSION 3.10)

project(Cluster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(zenohc_DIR "/usr/local/lib/cmake/zenohc")
set(zenohcxx_DIR "/usr/local/lib/cmake/zenohcxx")

find_package(Qt6 COMPONENTS Core Quick DBus REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(Cluster/include)
qt_add_resources(QT_RESOURCES_HCA ./Cluster/ui/resources.qrc)


add_executable(InstrumentClusterApp
    ${QT_RESOURCES_HCA}
    ./Cluster/src/main.cpp
    ./Cluster/src/InstrumentCluster.cpp
    ./Cluster/include/InstrumentCluster.hpp
)

add_executable(MiddleWareApp
    ./MiddleWare/src/main.cpp
)

target_link_libraries(InstrumentClusterApp zenohcxx::zenohc -lm -ldl Qt6::Core Qt6::DBus Qt6::Quick)
target_link_libraries(MiddleWareApp PRIVATE zenohcxx::zenohc)