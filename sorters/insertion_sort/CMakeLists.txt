get_filename_component(curr_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${curr_dir_name})

add_library( ${curr_dir_name} sort.cpp )
target_link_libraries(${curr_dir_name} sorter)