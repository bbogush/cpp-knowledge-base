add_executable(composite composite.cpp)

target_compile_features(composite PRIVATE cxx_std_20)
target_compile_options(composite PRIVATE -Wall -Wextra -Wpedantic)

