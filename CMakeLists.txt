cmake_minimum_required(VERSION 3.20)
project(TestMe VERSION 1.0)


if(TESTME)
    add_compile_definitions(TEST)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(ProjectConfig.h.in ProjectConfig.h)

add_subdirectory(Mutils)
add_subdirectory(Malgorithm)
add_subdirectory(MDataStruct)
add_subdirectory(MConfig)


add_executable(TestMe main.cpp)
option(USE_YAML "use yaml" OFF)

list(APPEND thirdLib )

target_link_directories(
        TestMe
        PUBLIC
        ThirdParty
)


if (USE_YAML)
    message("hello")
    list(APPEND thirdLib libyaml-cppd.a)
endif()

target_link_libraries(
        TestMe
        PUBLIC
        Mutils
        Malgorithm
        MDataStruct
        MConfig
        ${thirdLib}
)

target_include_directories(
        TestMe
        PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}
)