add_executable(command command.cpp)

target_compile_features(command PRIVATE cxx_std_20)
target_compile_options(command PRIVATE -Wall -Wextra -Wpedantic)

