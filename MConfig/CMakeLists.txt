
file(GLOB_RECURSE all_source ./*.cpp)
add_library(MConfig ${all_source})

include_directories(${CMAKE_CURRENT_BINARY_DIR})


target_include_directories(MConfig INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${PROJECT_SOURCE_DIR}/Mutils
        PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty)


target_link_libraries(MConfig  Mutils)