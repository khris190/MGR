cmake_minimum_required(VERSION 3.11.0)

set(VERSION "1.1.5")
project(GenerativeArt LANGUAGES CXX CUDA VERSION ${VERSION})
set(BINARY_DIR bin)
set(INCLUDE_DIR include)


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

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)  

include(CPack)
find_package(PNG REQUIRED)
find_package(Cairo REQUIRED)
find_package(CUDA  REQUIRED)


SET(LIBS ${LIBS} ${Cairo_LIBRARIES} -lcairo -lX11 ${GLM_LIBRARIES} CUDA_FITNESS MY_UTILS)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

add_dependencies(GenerativeArt CUDA_FITNESS MY_UTILS)
target_link_libraries(GenerativeArt ${LIBS})



target_include_directories(GenerativeArt PUBLIC ${Cairo_INCLUDE_DIRS} ${PNG_INCLUDE_DIR})
target_include_directories(GenerativeArt PRIVATE ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

SET (EXECUTABLE_OUTPUT_PATH ../${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${BINARY_DIR})

enable_testing()

file(GLOB TEST_EXECS
    ${TESTS_DIR}/*
)

foreach(TEST_EXEC ${TEST_EXECS})
    string(REGEX REPLACE "^.*/" "" TEST_NAME ${TEST_EXEC} )
    
    add_test(${TEST_NAME} ${TEST_EXEC})

endforeach(TEST_EXEC ${TEST_EXECS})
