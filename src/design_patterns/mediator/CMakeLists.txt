add_executable(mediator mediator.cpp)

target_compile_features(mediator PRIVATE cxx_std_20)
target_compile_options(mediator PRIVATE -Wall -Wextra -Wpedantic)

