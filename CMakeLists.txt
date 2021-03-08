cmake_minimum_required(VERSION 3.1)
project(aisd)

include("${CMAKE_SOURCE_DIR}/cmakes/get_all_directories.cmake")

add_subdirectory(sorters)

SUBDIRLIST( DIRS "${CMAKE_CURRENT_SOURCE_DIR}/sorters" )

add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${DIRS})