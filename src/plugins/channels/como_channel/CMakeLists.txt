
project( como_channel )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt6Core REQUIRED )
find_package( Qt6Gui REQUIRED )
find_package( Qt6Network REQUIRED )

set( SRC plugin.cpp )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../..
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../3rdparty/Como )

add_library( como_channel SHARED ${SRC} )

add_dependencies( como_channel Como )

set_target_properties( como_channel
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../App/plugins/como_channel"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../App/plugins/como_channel"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../App/plugins/como_channel"
)

target_link_libraries( como_channel Como Globe.Core Qt6::Gui Qt6::Network Qt6::Core )
