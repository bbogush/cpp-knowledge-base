add_executable(subsets subsets.cpp)

target_link_libraries(subsets PRIVATE project_options)
target_link_libraries(subsets PRIVATE project_features)

