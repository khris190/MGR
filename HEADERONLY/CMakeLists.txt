

cmake_minimum_required(VERSION 3.12)
project(HEADER_ONLY_LIB)

# Create an interface library target for the header-only library
add_library(HEADER_ONLY INTERFACE)

set(INCLUDE_DIR include)
file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR}/*.h
    ${INCLUDE_DIR}/*.hpp
)

set(HEADER_ONLY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(HEADER_ONLY INTERFACE ${HEADERS})
# Set the include directories for the library
target_include_directories(HEADER_ONLY
    INTERFACE
    ${HEADER_ONLY_INCLUDE}
)
set(HEADER_ONLY_INCLUDE ${HEADER_ONLY_INCLUDE} PARENT_SCOPE)
# add_library(HEADER_ONLY INTERFACE)
# target_include_directories(HEADER_ONLY INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
