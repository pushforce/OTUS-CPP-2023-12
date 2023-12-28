cmake_minimum_required(VERSION 3.22)

set(PATCH_VERSION "0" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.1.${PATCH_VERSION})

project(OTUS_CPP VERSION ${PROJECT_VESRION})


set(OTUS_CPP_SOURCE_DIR ${OTUS_CPP_SOURCE_DIR}/src)

configure_file(${OTUS_CPP_SOURCE_DIR}/version/env.hpp.in ${PROJECT_BINARY_DIR}/include/env.hpp)

enable_testing()

add_executable(helloworld_cli ${OTUS_CPP_SOURCE_DIR}/cli/helloworld.cpp)
add_library(version ${OTUS_CPP_SOURCE_DIR}/version/version.cpp)
add_executable(version_test ${OTUS_CPP_SOURCE_DIR}/version/version.test.cpp)

set_target_properties(helloworld_cli PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

target_include_directories(helloworld_cli
    PRIVATE "${OTUS_CPP_SOURCE_DIR}/version"
)

target_include_directories(version
    PRIVATE "${PROJECT_BINARY_DIR}/include"
)

target_link_libraries(helloworld_cli PRIVATE
    version
)

target_link_libraries(version_test PRIVATE GTest::gtest_main version)

include(GoogleTest)
gtest_discover_tests(version_test)
