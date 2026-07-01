add_executable(memento memento.cpp)

target_compile_features(memento PRIVATE cxx_std_20)
target_compile_options(memento PRIVATE -Wall -Wextra -Wpedantic)

