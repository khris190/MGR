cmake_minimum_required(VERSION 3.0.0)
project(MY_UTILS LANGUAGES CXX C CUDA VERSION 1.1.5)

enable_language(CUDA)
find_package(CUDA REQUIRED)

# set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_61,code=sm_61")

if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
  set(CMAKE_CUDA_ARCHITECTURES 61)
endif(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -msse2 ")


include(CTest)
enable_testing()

file(GLOB INCLUDES
    include/**/*.hpp
    include/**/*.h
)

file(GLOB SOURCES
    include/**/*.cpp
    include/**/*.c
)



add_library(${PROJECT_NAME} SHARED ${SOURCES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME}) 
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(MY_UTILS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/headerOnly )
set(MY_UTILS_INCLUDE ${MY_UTILS_INCLUDE} PARENT_SCOPE)
include_directories(${MY_UTILS_INCLUDE})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_UTILS_INCLUDE})
