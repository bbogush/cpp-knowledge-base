cmake_minimum_required(VERSION 3.20)
project(cpp-project-template VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_TESTING "Build unit tests" OFF)
option(ENABLE_COVERAGE "Instrument src/ targets for code coverage" OFF)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE -Wall -Wextra -Wpedantic -Werror)

if(ENABLE_COVERAGE)
  target_compile_options(project_options INTERFACE --coverage)
  target_link_options(project_options INTERFACE --coverage)
endif()

add_library(project_features INTERFACE)
target_compile_features(project_features INTERFACE cxx_std_20)

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

if(ENABLE_COVERAGE AND BUILD_TESTING)
  add_custom_target(coverage-report
    COMMAND "${CMAKE_COMMAND}"
            -DCOVERAGE_BINARY_DIR=${CMAKE_BINARY_DIR}
            -P ${CMAKE_SOURCE_DIR}/cmake/coverage_report.cmake
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMENT "Generating src/ coverage report (lcov CLI + HTML)"
    USES_TERMINAL
    VERBATIM
  )
endif()
