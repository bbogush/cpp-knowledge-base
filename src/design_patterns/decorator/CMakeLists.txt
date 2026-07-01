add_executable(decorator decorator.cpp)

target_compile_features(decorator PRIVATE cxx_std_20)
target_compile_options(decorator PRIVATE -Wall -Wextra -Wpedantic)

