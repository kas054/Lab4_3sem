cmake_minimum_required(VERSION 3.20)
project(Lab4_3sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab4_3sem main.cpp Basic/Armament.cpp Basic/Armament.h Ships/Ship.cpp Ships/Ship.h Table/Table.h Mission/Mission.cpp Mission/Mission.h Mission/Basic_config.cpp Mission/Game.cpp)
add_subdirectory(Google_tests)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Lab4_3sem sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
