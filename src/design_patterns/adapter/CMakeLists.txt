add_executable(adapter adapter.cpp)

target_link_libraries(adapter PRIVATE project_options)
target_link_libraries(adapter PRIVATE project_features)

