add_executable(strategy strategy.cpp)

target_compile_features(strategy PRIVATE cxx_std_20)
target_compile_options(strategy PRIVATE -Wall -Wextra -Wpedantic)

