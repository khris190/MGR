cmake_minimum_required(VERSION 3.27.0)

set(VERSION "1.1.5")
project(GenerativeArt LANGUAGES CXX C CUDA VERSION ${VERSION})
set(BINARY_DIR bin)
set(INCLUDE_DIR include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(VERSION="${VERSION}")
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_CXX_FLAGS_DEBUG "-g -D DEBUG")


file(GLOB_RECURSE SOURCES
    ${INCLUDE_DIR}/*.c
    ${INCLUDE_DIR}/*.cpp
)
file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR}/*.h
    ${INCLUDE_DIR}/*.hpp
)

# Set the path to your shader files
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")
# Add the shader files to your project's resources
file(GLOB_RECURSE SHADER_FILES "${SHADER_DIR}/*.vert" "${SHADER_DIR}/*.frag")

# Copy the shader files to the build directory
foreach(SHADER_FILE ${SHADER_FILES})
    string(REPLACE "${SHADER_DIR}/" "" SHADER_FILE_LOCAL_PATH ${SHADER_FILE})
    configure_file(${SHADER_FILE} "../${BINARY_DIR}/shaders/${SHADER_FILE_LOCAL_PATH}" COPYONLY)
endforeach()

add_subdirectory(CUDA_FITNESS)
add_subdirectory(UTILS)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)  

include(CPack)
find_package(PNG REQUIRED)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost COMPONENTS )

find_library(CUDART_LIBRARY cudart ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


SET(LIBS ${LIBS} -lcairo ${Boost_LIBRARIES} -lX11 ${GLEW_LIBRARIES} CUDA_FITNESS MY_UTILS glfw OpenGL::GL -lGL -lGLU -lglut -lGL -lpthread -lXrandr -lXi -ldl -lcuda ${CUDART_LIBRARY} ${CUDA_CUDA_LIBRARY} ${OPENGL_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} )

target_include_directories(${PROJECT_NAME} PUBLIC ${PNG_INCLUDE_DIR} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR}  )
target_include_directories(${PROJECT_NAME} INTERFACE ${HEADER_ONLY_INCLUDE})
add_dependencies(${PROJECT_NAME} CUDA_FITNESS MY_UTILS)
target_link_libraries(${PROJECT_NAME} ${LIBS})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

SET (EXECUTABLE_OUTPUT_PATH ../${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${BINARY_DIR})

enable_testing()

set(TESTS_DIR "tests")
file(GLOB TEST_SOURCES
    ${TESTS_DIR}/*.cpp
    ${TESTS_DIR}/**/*.cpp
    ${TESTS_DIR}/*.c
    ${TESTS_DIR}/**/*.c
)
foreach(TEST_SOURCE ${TEST_SOURCES})
    # string(REGEX REPLACE "^.*/" "" TEST_NAME ${TEST_SOURCE} )
    string(REGEX REPLACE ".+/(.+)\\..+" "\\1" TEST_NAME ${TEST_SOURCE})
    add_executable(
        ${TEST_NAME} ${TEST_SOURCE}  ${SOURCES}
    )
    target_include_directories(${TEST_NAME} PUBLIC ${PNG_INCLUDE_DIR} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    target_include_directories(${TEST_NAME} PRIVATE ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR}  )
    target_include_directories(${TEST_NAME} INTERFACE ${HEADER_ONLY_INCLUDE})
    
    target_link_libraries(
        ${TEST_NAME} GTest::gtest_main ${LIBS}
    )
    include(GoogleTest)   
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
endforeach(TEST_SOURCE ${TEST_SOURCES})
