
TEMPLATE = app
TARGET = LogViewer.App
DESTDIR = ../..
QT += core gui network sql widgets multimedia
CONFIG += windows c++14
DEFINES += ARGS_QSTRING_BUILD CFGFILE_QT_SUPPORT

win32 {
    RC_FILE = log_viewer.rc
}

RESOURCES = log_viewer_resources.qrc

HEADERS += mainwindow.hpp \
           configuration.hpp \
           log.hpp

SOURCES += main.cpp \
           mainwindow.cpp \
           configuration.cpp \
           log.cpp

include ( ../../3rdparty/Args/Args/Args.pri )

unix|win32: LIBS += -L$$OUT_PWD/../../ -lGlobe.Core

INCLUDEPATH += $$PWD/../../ $$PWD/../../3rdparty/cfgfile $$PWD/../ $$PWD/../../3rdparty/Como $$PWD/../../3rdparty/Args
DEPENDPATH += $$PWD/../../ $$PWD/../../3rdparty/cfgfile $$PWD/../ $$PWD/../../3rdparty/Como $$PWD/../../3rdparty/Args

unix|win32: LIBS += -L$$OUT_PWD/../../3rdparty/Como/lib/ -lComo

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/Como/lib/Como.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/Como/lib/libComo.a

macx {
	QMAKE_LFLAGS += -Wl,-rpath,@loader_path/.,-rpath,@executable_path/.
} else:linux-* {
	QMAKE_RPATHDIR += \$\$ORIGIN
	QMAKE_RPATHDIR += \$\$ORIGIN/.
	RPATH = $$join( QMAKE_RPATHDIR, ":" )

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${RPATH}\'
	QMAKE_RPATHDIR =
}
