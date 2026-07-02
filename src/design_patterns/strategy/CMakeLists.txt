add_executable(strategy strategy.cpp)

target_link_libraries(strategy PRIVATE project_options)
target_link_libraries(strategy PRIVATE project_features)

