cmake_minimum_required(VERSION 3.5)
project(golite)

# Define options/variables
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Prepare build directory
file(MAKE_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/include/bison
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/flex
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/bison)

# -I
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/cpp/include)

# Load Flex and Bison
find_package(BISON)
find_package(FLEX)
if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Flex package was not found")
elseif(NOT BISON_FOUND)
    message(FATAL_ERROR "Bison package was not found")
endif()

# Compile with C++11 option
add_compile_options(-std=c++11)

# Flex it!
flex_target(goflex ${PROJECT_SOURCE_DIR}/etc/flex/golang.l
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/flex/golang_flex.cpp)

# Bison it!
bison_target(gobison ${PROJECT_SOURCE_DIR}/etc/bison/golang.y
        ${CMAKE_CURRENT_BINARY_DIR}/cpp/src/bison/golang_bison.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/cpp/include/bison/golang_bison.h)

# Find all cpp files
file(GLOB_RECURSE PROJECT_SOURCE_FILES src/*/*.cpp)

# Build c++ files
add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES}
        ${BISON_gobison_OUTPUTS}
        ${FLEX_goflex_OUTPUTS})
target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES} )

# Include scaner parser sub-project
add_subdirectory(etc/scan_parse)
