add_executable(visitor visitor.cpp)

target_link_libraries(visitor PRIVATE project_options)
target_link_libraries(visitor PRIVATE project_features)

