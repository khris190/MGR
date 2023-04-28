cmake_minimum_required(VERSION 3.0)
project(tests VERSION 0.0.1 LANGUAGES CXX)

file(GLOB TESTS
    **/*.cpp
)

# add_compile_definitions("DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
# Prepare doctest for other targets to use
find_package(doctest REQUIRED)

# Make test executable
if(NOT PROJECT_IS_TOP_LEVEL)
  set(BINARY_DIR ../../bin)
else()
    set(BINARY_DIR ../bin)

endif()
set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_DIR}/tests)
set(TESTS_DIR ${TESTS_DIR} PARENT_SCOPE)

SET (EXECUTABLE_OUTPUT_PATH  ${TESTS_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR})


foreach(TEST_SOURCE_FILE ${TESTS})
    string( REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE_FILE} )
    string(REGEX REPLACE "^.*/" "" TEST_NAME ${TEST_NAME} )
    add_executable(${TEST_NAME} ${TEST_SOURCE_FILE})
    add_dependencies(${TEST_NAME} CUDA_FITNESS MY_UTILS)
    target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
    target_link_libraries(${TEST_NAME} doctest::doctest)

endforeach(TEST_SOURCE_FILE ${TESTS})