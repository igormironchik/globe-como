
TEMPLATE = app
TARGET = Globe
DESTDIR = ..
QT += core gui network
CONFIG += console

RESOURCES = resources.qrc

HEADERS += application_cfg.hpp \
           channel_attributes.hpp \
           channels.hpp \
           channels_cfg.hpp \
           channels_list.hpp \
           channel_timeout_widget.hpp \
           channels_to_show.hpp \
           channel_widget.hpp \
           db.hpp \
           mainwindow.hpp \
           mainwindow_cfg.hpp \
           window_state_cfg.hpp \
           utils.hpp

SOURCES += application_cfg.cpp \
           channel_attributes.cpp \
           channels.cpp \
           channels_cfg.cpp \
           channels_list.cpp \
           channel_timeout_widget.cpp \
           channels_to_show.cpp \
           channel_widget.cpp \
           db.cpp \
           mainwindow.cpp \
           mainwindow_cfg.cpp \
           main.cpp \
           window_state_cfg.cpp \
           utils.cpp

FORMS	 = channels_to_show.ui \
           channel_attributes.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo
else:symbian: LIBS += -lQtConfFile -lComo
else:unix: LIBS += -L$$OUT_PWD/../lib -lQtConfFile -lComo

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QtConfFile.lib $$OUT_PWD/../lib/Como.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QtConfFile.lib $$OUT_PWD/../lib/Como.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../lib/libQtConfFile.a $$OUT_PWD/../lib/libComo.a