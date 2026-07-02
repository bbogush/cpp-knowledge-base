add_executable(flyweight flyweight.cpp)

target_link_libraries(flyweight PRIVATE project_options)
target_link_libraries(flyweight PRIVATE project_features)

