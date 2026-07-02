add_executable(composite composite.cpp)

target_link_libraries(composite PRIVATE project_options)
target_link_libraries(composite PRIVATE project_features)

