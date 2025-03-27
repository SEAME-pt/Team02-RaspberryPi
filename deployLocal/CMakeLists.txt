cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(HandCluster)

find_package(Qt5 COMPONENTS Core Quick DBus REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)


qt_add_resources(QT_RESOURCES_HCA ../Clusters/HandCluster/ui/resources.qrc)
add_executable(HandClusterLocalInstance
    ${QT_RESOURCES_HCA}
    ../Clusters/HandCluster/src/main.cpp
    ../Clusters/HandCluster/src/InstrumentCluster.cpp
    ../Clusters/HandCluster/include/InstrumentCluster.hpp
)

target_link_libraries(HandClusterLocalInstance zenohcxx::zenohc -lm -ldl Qt5::Core Qt5::DBus Qt5::Quick)
