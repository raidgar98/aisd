set(CMAKE_AUTOMOC ON)
cmake_minimum_required(VERSION 3.1)
project(aisd)


set( ${CMAKE_CXX_STANDARD} 20 )
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-w")

include("${CMAKE_SOURCE_DIR}/cmakes/get_all_directories.cmake")

add_subdirectory(collections)
add_subdirectory(sorters)

SUBDIRLIST( DIRS "${CMAKE_CURRENT_SOURCE_DIR}/sorters" )

add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${DIRS} pthread PRIVATE mylist)