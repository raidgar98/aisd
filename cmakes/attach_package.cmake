cmake_minimum_required(VERSION 3.1)

MACRO(attach_boost)

	set(variadic ${ARGN})
	find_package(Boost 1.65 REQUIRED COMPONENTS ${variadic} )

ENDMACRO()
