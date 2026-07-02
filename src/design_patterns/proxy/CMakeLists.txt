add_executable(proxy proxy.cpp)

target_link_libraries(proxy PRIVATE project_options)
target_link_libraries(proxy PRIVATE project_features)

