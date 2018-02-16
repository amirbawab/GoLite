cmake_minimum_required(VERSION 3.5)
project(scan_parse)

# Build c++ files
add_executable(${PROJECT_NAME}
        ./src/scan_parse/scan_parse.cpp
        ../../src/lib/bison.cpp
        ../../src/lib/utils.cpp
        ${BISON_gobison_OUTPUTS}
        ${FLEX_goflex_OUTPUTS})
target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES} )
