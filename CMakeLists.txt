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

# include_directories(Clusters/include)
include_directories(Clusters/HandCluster/include)
# Add Resource File (QML and Other Resources)
# qt_add_resources(QT_RESOURCES_ICA ./Clusters/InstrumentCluster/ui/resources.qrc)
qt_add_resources(QT_RESOURCES_HCA ./Clusters/HandCluster/ui/resources.qrc)

# Define Executable Target
# add_executable(InstrumentClusterApp
#     ${QT_RESOURCES_ICA}
#     ./Clusters/InstrumentCluster/src/main.cpp
#     ./Clusters/InstrumentCluster/src/InstrumentCluster.cpp
#     ./Clusters/InstrumentCluster/include/InstrumentCluster.hpp
# )

add_executable(HandClusterB
    ${QT_RESOURCES_HCA}
    ./Clusters/HandCluster/src/main.cpp
    ./Clusters/HandCluster/src/InstrumentCluster.cpp
    ./Clusters/HandCluster/include/InstrumentCluster.hpp
)

add_executable(MiddleWareApp
    ./MiddleWare/src/main.cpp
)

# target_link_libraries(InstrumentClusterApp zenohcxx::zenohc -lm -ldl Qt6::Core Qt6::DBus Qt6::Quick)

target_link_libraries(HandClusterB zenohcxx::zenohc -lm -ldl Qt6::Core Qt6::DBus Qt6::Quick)

target_link_libraries(MiddleWareApp PRIVATE zenohcxx::zenohc)
