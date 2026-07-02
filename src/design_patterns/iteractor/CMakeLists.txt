add_executable(iterator iterator.cpp)

target_link_libraries(iterator PRIVATE project_options)
target_link_libraries(iterator PRIVATE project_features)

