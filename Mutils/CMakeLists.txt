
file(GLOB_RECURSE all_source ./*.cpp)
add_library(Mutils ${all_source})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(Mutils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})