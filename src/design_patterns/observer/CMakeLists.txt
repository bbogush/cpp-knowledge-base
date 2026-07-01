add_executable(observer observer.cpp)

target_compile_features(observer PRIVATE cxx_std_20)
target_compile_options(observer PRIVATE -Wall -Wextra -Wpedantic)

