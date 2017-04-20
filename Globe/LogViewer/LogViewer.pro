
TEMPLATE = app
TARGET = LogViewer.App
DESTDIR = ../..
QT += core gui network sql widgets multimedia xml
CONFIG += windows

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

include ( ../../QtArg/QtArg/qtarg.pri )

unix|win32: LIBS += -L$$OUT_PWD/../../ -lGlobe.Core

INCLUDEPATH += $$PWD/../../ $$PWD/../../QtConfFile $$PWD/../ $$PWD/../../Como
DEPENDPATH += $$PWD/../../ $$PWD/../../QtConfFile $$PWD/../ $$PWD/../../Como

unix|win32: LIBS += -L$$OUT_PWD/../../Como/lib/ -lComo \
    -L$$OUT_PWD/../../QtConfFile/lib/ -lQtConfFile

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../Como/lib/Como.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../Como/lib/libComo.a

macx {
	QMAKE_LFLAGS += -Wl,-rpath,@loader_path/.,-rpath,@executable_path/.
} else:linux-* {
	QMAKE_RPATHDIR += \$\$ORIGIN
	QMAKE_RPATHDIR += \$\$ORIGIN/.
	RPATH = $$join( QMAKE_RPATHDIR, ":" )

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${RPATH}\'
	QMAKE_RPATHDIR =
}
