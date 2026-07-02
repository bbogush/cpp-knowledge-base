add_executable(mediator mediator.cpp)

target_link_libraries(mediator PRIVATE project_options)
target_link_libraries(mediator PRIVATE project_features)

