add_executable(command command.cpp)

target_link_libraries(command PRIVATE project_options)
target_link_libraries(command PRIVATE project_features)

