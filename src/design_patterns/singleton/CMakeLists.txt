add_executable(singleton singleton.cpp)

target_compile_features(singleton PRIVATE cxx_std_20)
target_compile_options(singleton PRIVATE -Wall -Wextra -Wpedantic)

