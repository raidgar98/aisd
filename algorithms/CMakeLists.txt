include("${CMAKE_SOURCE_DIR}/cmakes/attach_package.cmake")
include("${CMAKE_SOURCE_DIR}/cmakes/get_all_directories.cmake")

SUBDIRLIST( DIRS ${CMAKE_CURRENT_SOURCE_DIR} )

attach_boost(stacktrace_addr2line stacktrace_noop stacktrace_basic)

FOREACH( VAR ${DIRS} )
	add_subdirectory(${VAR})
ENDFOREACH()
