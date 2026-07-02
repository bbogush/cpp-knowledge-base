cmake_minimum_required(VERSION 3.20)
project(cpp-project-template VERSION 0.1.0 LANGUAGES CXX)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE -Wall -Wextra -Wpedantic -Werror)

add_library(project_features INTERFACE)
target_compile_features(project_features INTERFACE cxx_std_20)

option(BUILD_TESTING "Build unit tests" OFF)

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
