add_executable(visitor visitor.cpp)

target_compile_features(visitor PRIVATE cxx_std_20)
target_compile_options(visitor PRIVATE -Wall -Wextra -Wpedantic)

