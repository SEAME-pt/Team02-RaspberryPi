cmake_minimum_required(VERSION 3.10)
project(HandCluster)

set(CMAKE_CXX_STANDARD 17)

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
qt_add_resources(QT_RESOURCES_HCA ../Clusters/HandCluster/ui/resources.qrc)

# Executável principal
add_executable(HandClusterLocalInstance
    ${QT_RESOURCES_HCA}
    ../Clusters/HandCluster/src/main.cpp
    ../Clusters/HandCluster/src/InstrumentCluster.cpp
    ../Clusters/HandCluster/include/InstrumentCluster.hpp
)

# Executável de testes
add_executable(HandClusterTests
    ${QT_RESOURCES_HCA}
    ../Clusters/HandCluster/src/InstrumentCluster.cpp
    ../Clusters/HandCluster/include/InstrumentCluster.hpp
    ../Clusters/HandCluster/tests/InstrumentClusterTest.cpp
    ../Clusters/HandCluster/tests/InstrumentClusterTest.hpp
)

# Linka bibliotecas
target_link_libraries(HandClusterLocalInstance
    zenohcxx::zenohc
    Qt5::Core Qt5::DBus Qt5::Quick
    -lm -ldl
)

target_link_libraries(HandClusterTests
    zenohcxx::zenohc
    Qt5::Core Qt5::DBus Qt5::Quick Qt5::Test
    -lm -ldl
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Adding coverage flags")
    add_compile_options(--coverage)
    link_libraries(gcov)
endif()

