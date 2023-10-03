cmake_minimum_required(VERSION 3.11.0)

set(VERSION "1.1.5")
project(GenerativeArt LANGUAGES CXX C CUDA VERSION ${VERSION})
set(BINARY_DIR bin)
set(INCLUDE_DIR include)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(VERSION="${VERSION}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

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
    get_filename_component(FILENAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} "../${BINARY_DIR}/shaders/${FILENAME}" COPYONLY)
endforeach()



add_subdirectory(CUDA_FITNESS)
add_subdirectory(UTILS)
add_subdirectory(HEADERONLY)
add_subdirectory(tests)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)  

include(CPack)
find_package(PNG REQUIRED)
find_package(Cairo REQUIRED)
# find_package(CUDA REQUIRED)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)


SET(LIBS ${LIBS} ${Cairo_LIBRARIES} ${GLUT_LIBRARY} -lcairo -lX11 ${GLM_LIBRARIES} ${GLEW_LIBRARIES} CUDA_FITNESS MY_UTILS glfw OpenGL::GL -lGL -lGLU -lglut -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lcuda HEADER_ONLY ${CUDA_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${OPENGL_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} )

target_include_directories(GenerativeArt PUBLIC ${Cairo_INCLUDE_DIRS} ${PNG_INCLUDE_DIR} ${CUDA_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})
target_include_directories(GenerativeArt PRIVATE ${CUDA_FITNESS_INCLUDE} ${MY_UTILS_INCLUDE} ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR} )
target_include_directories(GenerativeArt INTERFACE ${HEADER_ONLY_INCLUDE})
add_dependencies(GenerativeArt CUDA_FITNESS MY_UTILS)
target_link_libraries(GenerativeArt ${LIBS})


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
