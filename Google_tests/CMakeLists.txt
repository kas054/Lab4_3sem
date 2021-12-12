project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run ../Ship.cpp ../Armament.cpp T_Ships.cpp ../Basic_config.cpp)

target_link_libraries(Google_Tests_run)

target_link_libraries(Google_Tests_run gtest gtest_main)