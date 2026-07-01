add_executable(proxy proxy.cpp)

target_compile_features(proxy PRIVATE cxx_std_20)
target_compile_options(proxy PRIVATE -Wall -Wextra -Wpedantic)

