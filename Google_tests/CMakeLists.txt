project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run ../Ships/Ship.cpp ../Basic/Armament.cpp T_Ships.cpp  T_Armament.cpp)

target_link_libraries(Google_Tests_run)
target_link_libraries(Google_Tests_run gtest gtest_main)

add_executable(Google_Test_Armament ../Basic/Armament.cpp T_armament.cpp)
add_executable(Google_Test_Ship  T_Ships.cpp ../Ships/Ship.cpp ../Basic/Armament.cpp)
target_link_libraries(Google_Test_Armament gtest gtest_main)
target_link_libraries(Google_Test_Ship gtest gtest_main)