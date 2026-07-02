add_executable(shared_ptr shared_ptr.cpp)

target_link_libraries(shared_ptr PRIVATE project_options)
target_link_libraries(shared_ptr PRIVATE project_features)

