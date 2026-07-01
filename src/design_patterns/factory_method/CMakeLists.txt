add_executable(factory_method factory_method.cpp)

target_compile_features(factory_method PRIVATE cxx_std_20)
target_compile_options(factory_method PRIVATE -Wall -Wextra -Wpedantic)

