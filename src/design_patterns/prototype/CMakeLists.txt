add_executable(prototype prototype.cpp)

target_link_libraries(prototype PRIVATE project_options)
target_link_libraries(prototype PRIVATE project_features)

