add_executable(iterator iterator.cpp)

target_compile_features(iterator PRIVATE cxx_std_20)
target_compile_options(iterator PRIVATE -Wall -Wextra -Wpedantic)

