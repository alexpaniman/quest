add_executable(quest main.cpp)

target_include_directories(quest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(quest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

target_link_libraries(quest quest-lib fmt)
