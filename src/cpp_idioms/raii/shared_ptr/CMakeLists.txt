add_executable(shared_ptr shared_ptr.cpp)

target_compile_features(shared_ptr PRIVATE cxx_std_20)
target_compile_options(shared_ptr PRIVATE -Wall -Wextra -Wpedantic)

