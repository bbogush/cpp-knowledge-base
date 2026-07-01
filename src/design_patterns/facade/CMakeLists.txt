add_executable(facade facade.cpp)

target_compile_features(facade PRIVATE cxx_std_20)
target_compile_options(facade PRIVATE -Wall -Wextra -Wpedantic)

