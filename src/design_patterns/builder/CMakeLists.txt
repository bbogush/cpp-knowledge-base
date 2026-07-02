add_executable(builder builder.cpp)

target_link_libraries(builder PRIVATE project_options)
target_link_libraries(builder PRIVATE project_features)

