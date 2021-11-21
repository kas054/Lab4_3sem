project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run Test.cpp ../Armament.cpp T_Armament.cpp T_Ships.cpp)

target_link_libraries(Google_Tests_run)

target_link_libraries(Google_Tests_run gtest gtest_main)