cmake_minimum_required(VERSION 3.10)
project(OpenEarthGnomes)

# Main executable
add_executable(main_app src/main.cpp)

# Tests
enable_testing()
add_executable(tests_executable tests/basic_test.cpp tests/catch_amalgamated.cpp)
target_include_directories(tests_executable PRIVATE tests)
add_test(NAME basic_test COMMAND tests_executable)
