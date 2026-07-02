add_executable(decorator decorator.cpp)

target_link_libraries(decorator PRIVATE project_options)
target_link_libraries(decorator PRIVATE project_features)

