
cmake_minimum_required( VERSION 3.1 )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release"
		CACHE STRING "Choose the type of build."
		FORCE )
endif( NOT CMAKE_BUILD_TYPE )

SET( CMAKE_CXX_STANDARD 14 )

SET( CMAKE_CXX_STANDARD_REQUIRED ON )

project( Globe )

configure_file( example/build_directory.in ${CMAKE_CURRENT_SOURCE_DIR}/example/build_directory )

add_subdirectory( 3rdparty/Como )
add_subdirectory( src )
