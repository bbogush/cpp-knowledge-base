add_executable(memento memento.cpp)

target_link_libraries(memento PRIVATE project_options)
target_link_libraries(memento PRIVATE project_features)

