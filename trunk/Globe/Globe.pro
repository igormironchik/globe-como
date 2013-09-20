
TEMPLATE = app
TARGET = Globe
DESTDIR = ..
QT += core gui network sql widgets multimedia
CONFIG += console

win32 {
    RC_FILE = globe.rc
}

CONFIG(debug, debug|release) {
	DEFINES += GLOBE_DEBUG
}

RESOURCES = resources.qrc

HEADERS += application_cfg.hpp \
           channel_attributes.hpp \
           channel_name_dialog.hpp \
           channels.hpp \
           channels_cfg.hpp \
           channels_list.hpp \
           channel_timeout_widget.hpp \
           channels_to_show.hpp \
           channel_view.hpp \
           channel_view_window.hpp \
           channel_view_window_cfg.hpp \
           channel_view_window_model.hpp \
           channel_widget.hpp \
           color_for_level.hpp \
           color_for_level_cfg.hpp \
           color_picker.hpp \
           condition.hpp \
           condition_cfg.hpp \
           configuration.hpp \
           configuration_dialog.hpp \
           db.hpp \
           db_cfg.hpp \
		   globe_menu.hpp \
           launch_time.hpp \
           log.hpp \
           log_cfg.hpp \
           log_event_selector.hpp \
           log_event_view.hpp \
           log_event_view_model.hpp \
           log_event_view_window.hpp \
		   log_event_view_window_cfg.hpp \
           mainwindow.hpp \
           mainwindow_cfg.hpp \
           properties.hpp \
           properties_cfg.hpp \
           properties_cfg_filename_dialog.hpp \
           properties_dialog.hpp \
           properties_key_type_dialog.hpp \
           properties_model.hpp \
           properties_widget.hpp \
           properties_widget_model.hpp \
           select_query_navigation.hpp \
           scrolled_widget.hpp \
           sounds.hpp \
		   sounds_cfg.hpp \
		   sounds_disabled.hpp \
		   sounds_disabled_cfg.hpp \
		   sounds_disabled_data.hpp \
		   sounds_disabled_model.hpp \
		   sounds_disabled_view.hpp \
		   sounds_played_model.hpp \
		   sounds_played_view.hpp \
           source_manual_dialog.hpp \
           sources.hpp \
           sources_dialog.hpp \
           sources_mainwindow.hpp \
           sources_mainwindow_cfg.hpp \
           sources_model.hpp \
           sources_widget.hpp \
           sources_widget_view.hpp \
           window_state_cfg.hpp \
           windows_cfg.hpp \
		   with_menu.hpp \
           tool_window_object.hpp \
		   tool_window.hpp \
           utils.hpp

SOURCES += application_cfg.cpp \
           channel_attributes.cpp \
           channel_name_dialog.cpp \
           channels.cpp \
           channels_cfg.cpp \
           channels_list.cpp \
           channel_timeout_widget.cpp \
           channels_to_show.cpp \
           channel_view.cpp \
           channel_view_window.cpp \
           channel_view_window_cfg.cpp \
           channel_view_window_model.cpp \
           channel_widget.cpp \
           color_for_level.cpp \
           color_for_level_cfg.cpp \
           color_picker.cpp \
           condition.cpp \
           condition_cfg.cpp \
           configuration.cpp \
           configuration_dialog.cpp \
           db.cpp \
           db_cfg.cpp \
		   globe_menu.cpp \
           launch_time.cpp \
           log.cpp \
           log_cfg.cpp \
           log_event_selector.cpp \
           log_event_view.cpp \
           log_event_view_model.cpp \
           log_event_view_window.cpp \
		   log_event_view_window_cfg.cpp \
           mainwindow.cpp \
           mainwindow_cfg.cpp \
           main.cpp \
           properties.cpp \
           properties_cfg.cpp \
           properties_cfg_filename_dialog.cpp \
           properties_dialog.cpp \
           properties_key_type_dialog.cpp \
           properties_model.cpp \
           properties_widget.cpp \
           properties_widget_model.cpp \
           select_query_navigation.cpp \
           scrolled_widget.cpp \
           sounds.cpp \
		   sounds_cfg.cpp \
		   sounds_disabled.cpp \
		   sounds_disabled_cfg.cpp \
		   sounds_disabled_data.cpp \
		   sounds_disabled_model.cpp \
		   sounds_disabled_view.cpp \
		   sounds_played_model.cpp \
		   sounds_played_view.cpp \
           source_manual_dialog.cpp \
           sources.cpp \
           sources_dialog.cpp \
           sources_mainwindow.cpp \
           sources_mainwindow_cfg.cpp \
           sources_model.cpp \
           sources_widget.cpp \
           sources_widget_view.cpp \
           window_state_cfg.cpp \
           windows_cfg.cpp \
		   with_menu.cpp \
           tool_window_object.cpp \
		   tool_window.cpp \
           utils.cpp

FORMS	 = channels_to_show.ui \
           channel_name_dialog.ui \
           channel_attributes.ui \
           configuration_dialog.ui \
           log_event_selector.ui \
           properties_mainwindow.ui \
           properties_cfg_filename_dialog.ui \
           properties_key_type_dialog.ui \
           select_query_navigation.ui \
           source_manual_dialog.ui \
           sources_widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo
else:symbian: LIBS += -lQtConfFile -lComo
else:unix: LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QtConfFile.lib $$OUT_PWD/../lib/Como.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QtConfFile.lib $$OUT_PWD/../lib/Como.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../lib/libQtConfFile.a $$OUT_PWD/../lib/libComo.a

include ( ../QtArg/qtarg.pri )
