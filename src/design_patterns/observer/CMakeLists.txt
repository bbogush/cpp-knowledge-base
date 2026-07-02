add_executable(observer observer.cpp)

target_link_libraries(observer PRIVATE project_options)
target_link_libraries(observer PRIVATE project_features)

