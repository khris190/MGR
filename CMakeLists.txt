cmake_minimum_required(VERSION 3.11.0)

set(VERSION "1.1.5")
project(GenerativeArt LANGUAGES CXX CUDA VERSION ${VERSION})
set(BINARY_DIR ../bin)
set(INCLUDE_DIR include)

add_executable(${PROJECT_NAME} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(VERSION="${VERSION}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

set(CMAKE_CXX_FLAGS_DEBUG "-g -D DEBUG")


file(GLOB SOURCES
    ${INCLUDE_DIR}/*.*
    ${INCLUDE_DIR}/**/*.*
)

add_subdirectory(CUDA)
add_subdirectory(UTILS)
add_subdirectory(tests)


SET(LIBS ${LIBS} CUDA_FITNESS MY_UTILS)
SET(INCLUDES ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} include)

include_directories(${INCLUDES})
target_link_libraries(GenerativeArt ${LIBS})
add_dependencies(GenerativeArt CUDA_FITNESS MY_UTILS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

SET (EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

enable_testing()
# add_executable(tester ${SOURCES})
# target_include_directories(tester PUBLIC ${INCLUDES})
# target_link_libraries(tester PRIVATE  ${LIBS}) # I actually have other libraries to use here
# target_link_libraries(tester PUBLIC cmake_test)
# set_target_properties(tester PROPERTIES COMPILE_DEFINITIONS "TEST")
add_test(Tester ../bin/cmake_test)
