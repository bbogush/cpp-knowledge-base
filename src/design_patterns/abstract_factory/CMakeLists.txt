add_executable(abstract_factory abstract_factory.cpp)

target_compile_features(abstract_factory PRIVATE cxx_std_20)
target_compile_options(abstract_factory PRIVATE -Wall -Wextra -Wpedantic)

