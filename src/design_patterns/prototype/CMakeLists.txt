add_executable(prototype prototype.cpp)

target_compile_features(prototype PRIVATE cxx_std_20)
target_compile_options(prototype PRIVATE -Wall -Wextra -Wpedantic)

