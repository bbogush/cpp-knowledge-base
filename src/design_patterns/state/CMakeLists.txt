add_executable(state state.cpp)

target_link_libraries(state PRIVATE project_options)
target_link_libraries(state PRIVATE project_features)

