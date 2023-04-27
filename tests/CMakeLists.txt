cmake_minimum_required(VERSION 3.0)
project(cmake_test VERSION 0.0.1 LANGUAGES CXX)


file(GLOB TESTS
    **/*.cpp
)

# add_compile_definitions("DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
# Prepare doctest for other targets to use
find_package(doctest REQUIRED)

# Make test executable
add_executable(cmake_test ${TESTS})
add_dependencies(cmake_test CUDA_FITNESS MY_UTILS)
target_compile_features(cmake_test PRIVATE cxx_std_17)
target_link_libraries(cmake_test doctest::doctest)

SET (EXECUTABLE_OUTPUT_PATH ../${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${BINARY_DIR})s