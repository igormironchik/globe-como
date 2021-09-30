
TEMPLATE = app
TARGET = Globe
DESTDIR = ../..
QT += core gui widgets network sql multimedia
CONFIG += windows c++14
DEFINES += ARGS_QSTRING_BUILD CFGFILE_QT_SUPPORT

win32 {
    RC_FILE = globe.rc
}

SOURCES += main.cpp

exists( ../../como_defines.pri ) {
    include( ../../como_defines.pri )
}


unix|win32: LIBS += -L$$OUT_PWD/../../3rdparty/Como/lib/ -lComo

INCLUDEPATH += $$PWD/../../3rdparty/Como $$PWD/../ $$PWD/../../3rdparty/cfgfile $$PWD/../../3rdparty/args-parser
DEPENDPATH += $$PWD/../../3rdparty/Como $$PWD/../ $$PWD/../../3rdparty/cfgfile $$PWD/../../3rdparty/args-parser

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/Como/lib/Como.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/Como/lib/libComo.a


unix|win32: LIBS += -L$$OUT_PWD/../../ -lGlobe.Core

macx {
	QMAKE_LFLAGS += -Wl,-rpath,@loader_path/.,-rpath,@executable_path/.
} else:linux-* {
	QMAKE_RPATHDIR += \$\$ORIGIN
	QMAKE_RPATHDIR += \$\$ORIGIN/.
	RPATH = $$join( QMAKE_RPATHDIR, ":" )

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${RPATH}\'
	QMAKE_RPATHDIR =
}
