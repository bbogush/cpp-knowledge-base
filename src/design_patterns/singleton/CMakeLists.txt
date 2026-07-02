add_executable(singleton singleton.cpp)

target_link_libraries(singleton PRIVATE project_options)
target_link_libraries(singleton PRIVATE project_features)

