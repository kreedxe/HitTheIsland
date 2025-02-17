cmake_minimum_required(VERSION 3.30)
project(HitTheIsland)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Ball.cpp
    src/ConfigLoader.cpp
    src/Pad.cpp
    src/ScoreCounter.cpp
    src/Island.cpp
)

add_executable(HitTheIsland ${SOURCES})

set(SFML_DIR ${CMAKE_SOURCE_DIR}/dependencies/SFML/lib/cmake/SFML)
find_package(SFML 3 REQUIRED COMPONENTS System Graphics Audio Network)
target_link_libraries(HitTheIsland PRIVATE SFML::System SFML::Graphics SFML::Audio SFML::Network)
target_include_directories(HitTheIsland PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/json)