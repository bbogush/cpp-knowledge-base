add_executable(lru_cache lru_cache.cpp)

target_link_libraries(lru_cache PRIVATE project_options)
target_link_libraries(lru_cache PRIVATE project_features)

