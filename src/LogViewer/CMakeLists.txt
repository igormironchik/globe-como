
project( Globe.LogViewer )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt6Core REQUIRED )
find_package( Qt6Widgets REQUIRED )
find_package( Qt6Gui REQUIRED )
find_package( Qt6Network REQUIRED )
find_package( Qt6Sql REQUIRED )
find_package( Qt6Multimedia REQUIRED )

set( SRC main.cpp
    mainwindow.hpp
    mainwindow.cpp
    configuration.hpp
    configuration.cpp
    log.hpp
    log.cpp )

qt6_add_resources( SRC log_viewer_resources.qrc )

if( WIN32 )
	list( APPEND SRC log_viewer.rc )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/cfgfile
	${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/Como
	${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/args-parser )

add_definitions( -DARGS_QSTRING_BUILD -DCFGFILE_QT_SUPPORT )

add_executable( Globe.LogViewer ${SRC} )

add_dependencies( Globe.LogViewer Globe.Core )

target_link_libraries( Globe.LogViewer Globe.Core Qt6::Multimedia Qt6::Widgets Qt6::Gui Qt6::Network Qt6::Sql Qt6::Core )
