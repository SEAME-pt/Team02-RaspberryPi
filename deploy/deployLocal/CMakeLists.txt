cmake_minimum_required(VERSION 3.10)
project(HandCluster)

set(CMAKE_CXX_STANDARD 17)

set(zenohc_DIR "/usr/local/lib/cmake/zenohc")
set(zenohcxx_DIR "/usr/local/lib/cmake/zenohcxx")

# Habilita suporte a Qt
find_package(Qt5 COMPONENTS Core Quick DBus Test REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

# Flags de cobertura (somente para GCC)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

# Automatiza moc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Includes e libs locais
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Recursos Qt
qt_add_resources(QT_RESOURCES_HCA ../../Cluster/ui/resources.qrc)

# Executável principal
add_executable(InstrumentClusterLocalInstance
    ${QT_RESOURCES_HCA}
    ../../Cluster/src/main.cpp
    ../../Cluster/src/InstrumentCluster.cpp
    ../../Cluster/include/InstrumentCluster.hpp
)

# Linka bibliotecas
target_link_libraries(InstrumentClusterLocalInstance
    zenohcxx::zenohc
    Qt5::Core Qt5::DBus Qt5::Quick
    -lm -ldl
)


