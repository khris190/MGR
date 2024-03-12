cmake_minimum_required(VERSION 3.27.0)

set(VERSION "1.1.5")
project(GenerativeArt LANGUAGES C CXX CUDA VERSION ${VERSION})
set(BINARY_DIR bin)
set(INCLUDE_DIR include)
set(VCPKG_BUILD_TYPE release)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(VERSION="${VERSION}")
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")


set(CMAKE_CXX_FLAGS_DEBUG "-g -D DEBUG")


file(GLOB_RECURSE SOURCES
    ${INCLUDE_DIR}/*.c
    ${INCLUDE_DIR}/*.cpp
    ${INCLUDE_DIR}/*.cu
)
file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR}/*.h
    ${INCLUDE_DIR}/*.hpp
    UTILS/*.h
    UTILS/*.hpp
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

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)  

include(CPack)
find_package(PkgConfig REQUIRED)
pkg_check_modules(cairo REQUIRED IMPORTED_TARGET cairo)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

message(hello ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
# find_library(CUDART_LIBRARY cudart ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
find_package(CUDAToolkit)

SET(LIBS ${LIBS} PkgConfig::cairo ${Boost_LIBRARIES} ${GLEW_LIBRARIES} glfw OpenGL::GL ${CUDART_LIBRARY} ${CUDA_CUDA_LIBRARY} ${OPENGL_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PRIVATE ${DOCTEST_INCLUDE_DIR} ${INCLUDE_DIR}  )
target_include_directories(${PROJECT_NAME} INTERFACE ${HEADER_ONLY_INCLUDE})
target_link_libraries(${PROJECT_NAME} ${LIBS})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

SET (EXECUTABLE_OUTPUT_PATH ../${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${BINARY_DIR})

