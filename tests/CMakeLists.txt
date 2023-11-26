cmake_minimum_required(VERSION 3.11)
project(tests VERSION 0.0.1 LANGUAGES CXX)

file(GLOB TESTS
    **/*.cpp
)

find_package(doctest REQUIRED)

# Make test executable
if(NOT PROJECT_IS_TOP_LEVEL)
  set(BINARY_DIR ../../bin)
else()
    set(BINARY_DIR ../bin)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(GLOB_RECURSE SOURCES
    ${INCLUDE_DIR}/*.c
    ${INCLUDE_DIR}/*.cpp
)
file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR}/*.h
    ${INCLUDE_DIR}/*.hpp
)
find_package(PNG REQUIRED)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost COMPONENTS )


set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_DIR}/tests)
set(TESTS_DIR ${TESTS_DIR} PARENT_SCOPE)

SET (EXECUTABLE_OUTPUT_PATH  ${TESTS_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR})
SET(LIBS ${LIBS} -lcairo ${Boost_LIBRARIES} -lX11 ${GLEW_LIBRARIES} CUDA_FITNESS MY_UTILS glfw OpenGL::GL -lGL -lGLU -lglut -lGL -lpthread -lXrandr -lXi -ldl -lcuda ${CUDART_LIBRARY} ${CUDA_CUDA_LIBRARY} ${OPENGL_LIBRARIES})
foreach(TEST_SOURCE_FILE ${TESTS})
    get_filename_component(TEST_NAME ${TEST_SOURCE_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE_FILE} ${SOURCES})
    add_dependencies(${TEST_NAME} CUDA_FITNESS MY_UTILS)
    target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)

    target_include_directories(${TEST_NAME} PUBLIC ${PNG_INCLUDE_DIR} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    target_include_directories(${TEST_NAME} PRIVATE ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR}  )
    target_link_libraries(${TEST_NAME} doctest::doctest ${LIBS})
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach(TEST_SOURCE_FILE ${TESTS})