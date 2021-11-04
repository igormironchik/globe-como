
project( Core )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt6Core REQUIRED )
find_package( Qt6Widgets REQUIRED )
find_package( Qt6Gui REQUIRED )
find_package( Qt6Network REQUIRED )
find_package( Qt6Sql REQUIRED )
find_package( Qt6Multimedia REQUIRED )

add_definitions( -DGLOBE_CORE -DCFGFILE_QT_SUPPORT )

string( TOLOWER ${CMAKE_BUILD_TYPE} build_type )

if( build_type STREQUAL debug )
  add_definitions( -DGLOBE_CORE_DEBUG )
endif()

set( SRC application_cfg.hpp
    export.hpp
    channel_attributes.hpp
    channel_name_dialog.hpp
    channels.hpp
    channels_cfg.hpp
    channels_list.hpp
    channel_timeout_widget.hpp
    channels_to_show.hpp
    channel_view.hpp
    channel_view_window.hpp
    channel_view_window_cfg.hpp
    channel_view_window_model.hpp
    channel_widget.hpp
    color_for_level.hpp
    color_for_level_cfg.hpp
    color_picker.hpp
    condition.hpp
    condition_cfg.hpp
    configuration.hpp
    configuration_dialog.hpp
    db.hpp
    db_cfg.hpp
    globe_menu.hpp
    launch_time.hpp
    log.hpp
    log_cfg.hpp
    log_event_selector.hpp
    log_event_view.hpp
    log_event_view_model.hpp
    log_event_view_window.hpp
    log_event_view_window_cfg.hpp
    log_sources_selector.hpp
    log_sources_view.hpp
    log_sources_model.hpp
    log_sources_window.hpp
    log_sources_window_cfg.hpp
    mainwindow.hpp
    mainwindow_cfg.hpp
    properties.hpp
    properties_cfg.hpp
    properties_cfg_filename_dialog.hpp
    properties_dialog.hpp
    properties_key_type_dialog.hpp
    properties_manager.hpp
    properties_manager_view.hpp
    properties_map.hpp
    properties_model.hpp
    properties_widget.hpp
    properties_widget_model.hpp
    select_query_navigation.hpp
    scrolled_widget.hpp
    sounds.hpp
    sounds_cfg.hpp
    sounds_disabled.hpp
    sounds_disabled_cfg.hpp
    sounds_disabled_data.hpp
    sounds_disabled_model.hpp
    sounds_disabled_to_dialog.hpp
    sounds_disabled_view.hpp
    sounds_played_model.hpp
    sounds_played_view.hpp
    source_manual_dialog.hpp
    sources.hpp
    sources_dialog.hpp
    sources_mainwindow.hpp
    sources_mainwindow_cfg.hpp
    sources_model.hpp
    sources_widget.hpp
    sources_widget_view.hpp
    window_state_cfg.hpp
    windows_cfg.hpp
    with_menu.hpp
    tool_window_object.hpp
    tool_window.hpp
    utils.hpp
    word_wrap_delegate.hpp
    application_cfg.cpp
    channel_attributes.cpp
    channel_name_dialog.cpp
    channels.cpp
    channels_cfg.cpp
    channels_list.cpp
    channel_timeout_widget.cpp
    channels_to_show.cpp
    channel_view.cpp
    channel_view_window.cpp
    channel_view_window_cfg.cpp
    channel_view_window_model.cpp
    channel_widget.cpp
    color_for_level.cpp
    color_for_level_cfg.cpp
    color_picker.cpp
    condition.cpp
    condition_cfg.cpp
    configuration.cpp
    configuration_dialog.cpp
    db.cpp
    db_cfg.cpp
    globe_menu.cpp
    launch_time.cpp
    log.cpp
    log_cfg.cpp
    log_event_selector.cpp
    log_event_view.cpp
    log_event_view_model.cpp
    log_event_view_window.cpp
    log_event_view_window_cfg.cpp
    log_sources_selector.cpp
    log_sources_view.cpp
    log_sources_model.cpp
    log_sources_window.cpp
    log_sources_window_cfg.cpp
    mainwindow.cpp
    mainwindow_cfg.cpp
    properties.cpp
    properties_cfg.cpp
    properties_cfg_filename_dialog.cpp
    properties_dialog.cpp
    properties_key_type_dialog.cpp
    properties_manager.cpp
    properties_manager_view.cpp
    properties_map.cpp
    properties_model.cpp
    properties_widget.cpp
    properties_widget_model.cpp
    select_query_navigation.cpp
    scrolled_widget.cpp
    sounds.cpp
    sounds_cfg.cpp
    sounds_disabled.cpp
    sounds_disabled_cfg.cpp
    sounds_disabled_data.cpp
    sounds_disabled_model.cpp
    sounds_disabled_to_dialog.cpp
    sounds_disabled_view.cpp
    sounds_played_model.cpp
    sounds_played_view.cpp
    source_manual_dialog.cpp
    sources.cpp
    sources_dialog.cpp
    sources_mainwindow.cpp
    sources_mainwindow_cfg.cpp
    sources_model.cpp
    sources_widget.cpp
    sources_widget_view.cpp
    window_state_cfg.cpp
    windows_cfg.cpp
    with_menu.cpp
    tool_window_object.cpp
    tool_window.cpp
    utils.cpp
    word_wrap_delegate.cpp
    channels_to_show.ui
    channel_name_dialog.ui
    channel_attributes.ui
    configuration_dialog.ui
    log_event_selector.ui
    log_sources_selector.ui
    properties_mainwindow.ui
    properties_cfg_filename_dialog.ui
    properties_key_type_dialog.ui
    select_query_navigation.ui
    source_manual_dialog.ui
    sources_widget.ui
    sounds_disabled_to_dialog.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/enums.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/item_base_cfg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/mm_pixels.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scene.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scheme_cfg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/selectable.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/selection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/size_dialog.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/source.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/source_cfg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text_cfg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text_dialog.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/view.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/window_cfg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/aggregate.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/base_item.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scheme_utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/name_dlg.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/item_base_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/mm_pixels.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scheme_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/selection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/size_dialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/source.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/source_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text_dialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/view.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/window_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/aggregate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/selectable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/base_item.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scheme_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/name_dlg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/size_dialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/text_dialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/name_dlg.ui )

set( CMAKE_CXX_STANDARD 14 )

set( CMAKE_CXX_STANDARD_REQUIRED ON )

qt6_add_resources( SRC resources.qrc )
qt6_add_resources( SRC ${CMAKE_CURRENT_SOURCE_DIR}/../Scheme/scheme_resources.qrc )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/cfgfile
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/Como
	${CMAKE_CURRENT_SOURCE_DIR} )

add_library( Globe.Core SHARED ${SRC} )

add_dependencies( Globe.Core Como )

target_link_libraries( Globe.Core Como Qt6::Multimedia Qt6::Widgets Qt6::Gui Qt6::Network Qt6::Sql Qt6::Core )
