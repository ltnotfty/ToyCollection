

file(GLOB_RECURSE all_source ./*.cpp)

add_library(Malgorithm ${all_source})



target_include_directories(Malgorithm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})