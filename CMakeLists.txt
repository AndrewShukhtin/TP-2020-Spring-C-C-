cmake_minimum_required(VERSION 3.11)
project(hw1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror --pedantic")

include_directories(project/longest_arth_seq project/parser)

set(LIB_SOURCE_FILES
    project/longest_arth_seq/longest_arth_seq.c
    project/longest_arth_seq/test_longest_arth_seq.cpp
    project/parser/parse_input.c
    project/parser/test_parse_input.cpp
    )

add_library(longest_arth_seq_lib STATIC ${LIB_SOURCE_FILES})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package( GTest REQUIRED )
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# tests for longest_arth_seq.c
add_executable(test_longest_arth_seq.out project/longest_arth_seq/test_longest_arth_seq.cpp)
target_link_libraries(test_longest_arth_seq.out longest_arth_seq_lib)

target_link_libraries(test_longest_arth_seq.out ${GTEST_LIBRARIES})
target_link_libraries(test_longest_arth_seq.out pthread)

# tests for parse_input.c
add_executable(test_parse_input.out project/parser/test_parse_input.cpp)
target_link_libraries(test_parse_input.out longest_arth_seq_lib)

target_link_libraries(test_parse_input.out ${GTEST_LIBRARIES})
target_link_libraries(test_parse_input.out pthread)
