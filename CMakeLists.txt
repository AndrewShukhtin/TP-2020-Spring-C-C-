cmake_minimum_required(VERSION 3.10)
project(hw2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror --pedantic")

include_directories(
                    project/coordinate_average/coord
                    project/coordinate_average/coord_arrays
                    project/coordinate_average/sequential
                    project/coordinate_average/parallel
                    project/coordinate_average/utils)

set(COORD_MEAN_SRC
                    project/coordinate_average/coord/coord.c
                    project/coordinate_average/coord_arrays/coord_arrays.c
                    project/coordinate_average/sequential/coord_mean.c
                    project/coordinate_average/parallel/coord_mean_parall.c
                    project/coordinate_average/utils/utils.c)

#GTEST 
find_package(GTest REQUIRED)
include_directories(${GTEST_INLCUDE_DIRS})

add_library(_coord_mean_dl MODULE ${COORD_MEAN_SRC})
add_library(_coord_mean_static STATIC ${COORD_MEAN_SRC})

find_package(benchmark QUIET)
if (benchmark_FOUND)
  add_executable(gbenchmark.out project/coordinate_average/benchmark.cpp)
  target_link_libraries(gbenchmark.out
                                      benchmark::benchmark
                                      _coord_mean_static
                                      pthread)
endif()

# main project coordinate_avarage
add_executable(coordinate_avarage.out project/coordinate_average/main.c)
target_link_libraries(coordinate_avarage.out
                                            _coord_mean_static
                                            pthread)

add_executable(test_generator.out test_data/test_generator.cpp)

# STATIC SEQUENTIAL VS. DL SEQUENTIAL
add_executable(test_static_seq_vs_dl_seq.out
                      project/coordinate_average/tests/test_static_seq_vs_dl_seq.cpp)
target_link_libraries(test_static_seq_vs_dl_seq.out
                                            _coord_mean_static
                                            ${GTEST_LIBRARIES}
                                            ${CMAKE_DL_LIBS}
                                            pthread)

# STATIC PARALLEL VS. DL SEQUENTIAL
add_executable(test_static_parall_vs_dl_seq.out
                          project/coordinate_average/tests/test_static_parall_vs_dl_seq.cpp)
target_link_libraries(test_static_parall_vs_dl_seq.out
                                            _coord_mean_static
                                            ${GTEST_LIBRARIES}
                                            ${CMAKE_DL_LIBS}
                                            pthread)

# STATIC SEQUENTIAL VS. DL PARALLEL
add_executable(test_static_seq_vs_dl_parall.out
                           project/coordinate_average/tests/test_static_seq_vs_dl_parall.cpp)
target_link_libraries(test_static_seq_vs_dl_parall.out
                                            _coord_mean_static
                                            ${GTEST_LIBRARIES}
                                            ${CMAKE_DL_LIBS}
                                            pthread)

# STATIC PARALLEL VS. DL PARALLEL
add_executable(test_static_parall_vs_dl_parall.out
                      project/coordinate_average/tests/test_static_parall_vs_dl_parall.cpp)
target_link_libraries(test_static_parall_vs_dl_parall.out
                                            _coord_mean_static
                                            ${GTEST_LIBRARIES}
                                            ${CMAKE_DL_LIBS}
                                            pthread)


# COORD TESTS
add_executable(test_coord.out
                              project/coordinate_average/tests/test_coord.cpp
                              project/coordinate_average/coord/coord.c)
target_compile_options(test_coord.out INTERFACE
                              $<$<COMPILE_LANGUAGE:CXX>:--coverage>
                              $<$<COMPILE_LANGUAGE:C>:--coverage>)
target_link_libraries(test_coord.out
                              ${GTEST_LIBRARIES}
                              pthread)


# COORD_ARRAYS TESTS
add_executable(test_coord_arrays.out
                              project/coordinate_average/tests/test_coord_arrays.cpp
                              project/coordinate_average/coord_arrays/coord_arrays.c)
target_compile_options(test_coord_arrays.out INTERFACE
                              $<$<COMPILE_LANGUAGE:CXX>:--coverage>
                              $<$<COMPILE_LANGUAGE:C>:--coverage>)
target_link_libraries(test_coord_arrays.out
                              ${GTEST_LIBRARIES}
                              pthread)


# COORD_MEAN TESTS
add_executable(test_coord_mean.out
                              project/coordinate_average/tests/test_coord_mean.cpp
                              project/coordinate_average/coord/coord.c
                              project/coordinate_average/coord_arrays/coord_arrays.c
                              project/coordinate_average/sequential/coord_mean.c)
target_compile_options(test_coord_mean.out INTERFACE
                              $<$<COMPILE_LANGUAGE:CXX>:--coverage>
                              $<$<COMPILE_LANGUAGE:C>:--coverage>)
target_link_libraries(test_coord_mean.out
                              ${GTEST_LIBRARIES}
                              pthread)


# COORD_MEAN_PARALL TESTS
add_executable(test_coord_mean_parall.out
                              project/coordinate_average/tests/test_coord_mean_parall.cpp 
                              ${COORD_MEAN_SRC})
target_compile_options(test_coord_mean_parall.out INTERFACE
                              $<$<COMPILE_LANGUAGE:CXX>:--coverage>
                              $<$<COMPILE_LANGUAGE:C>:--coverage>)
target_link_libraries(test_coord_mean_parall.out
                              ${GTEST_LIBRARIES}
                              pthread)


# UTILITIES TESTS
add_executable(test_utils.out
                              project/coordinate_average/tests/test_utils.cpp
                              project/coordinate_average/utils/utils.c)
target_compile_options(test_utils.out INTERFACE
                              $<$<COMPILE_LANGUAGE:CXX>:--coverage>
                              $<$<COMPILE_LANGUAGE:C>:--coverage>)
target_link_libraries(test_utils.out
                              ${GTEST_LIBRARIES}
                              pthread)
