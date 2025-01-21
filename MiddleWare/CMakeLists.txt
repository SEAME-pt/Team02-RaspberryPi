cmake_minimum_required(VERSION 3.10)

project(Middelware LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(zenohc_DIR "/usr/local/lib/cmake/zenohc")
set(zenohcxx_DIR "/usr/local/lib/cmake/zenohcxx")

find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

# include(FetchContent)
# FetchContent_Declare(
#     Libs
#     GIT_REPOSITORY https://github.com/SEAME-pt/Team02-Libs
#     GIT_TAG main
# )
# FetchContent_MakeAvailable(Libs)   

# include_directories(${libs_SOURCE_DIR}/Communication/I2C/include)
# include_directories(${libs_SOURCE_DIR}/Communication/CAN/include)
# include_directories(${libs_SOURCE_DIR}/Peripherals/INA219/include) 

add_executable(middleWareApp
    ./src/main.cpp
)

target_link_libraries(middleWareApp PRIVATE zenohcxx::zenohc)
