add_executable(bridge bridge.cpp)

target_link_libraries(bridge PRIVATE project_options)
target_link_libraries(bridge PRIVATE project_features)

