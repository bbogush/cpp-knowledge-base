add_executable(facade facade.cpp)

target_link_libraries(facade PRIVATE project_options)
target_link_libraries(facade PRIVATE project_features)

