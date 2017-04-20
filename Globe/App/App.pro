
TEMPLATE = app
TARGET = Globe.App
DESTDIR = ../..
QT += core gui widgets network xml sql multimedia
CONFIG += windows

win32 {
    RC_FILE = globe.rc
}

SOURCES += main.cpp

include ( ../../QtArg/QtArg/qtarg.pri )

exists( ../../como_defines.pri ) {
    include( ../../como_defines.pri )
}


unix|win32: LIBS += -L$$OUT_PWD/../../Como/lib/ -lComo

INCLUDEPATH += $$PWD/../../Como
DEPENDPATH += $$PWD/../../Como

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../Como/lib/Como.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../Como/lib/libComo.a


unix|win32: LIBS += -L$$OUT_PWD/../../ -lGlobe.Core

INCLUDEPATH += $$PWD/../.. $$PWD/../../QtConfFile
DEPENDPATH += $$PWD/../.. $$PWD/../../QtConfFile

macx {
	QMAKE_LFLAGS += -Wl,-rpath,@loader_path/.,-rpath,@executable_path/.
} else:linux-* {
	QMAKE_RPATHDIR += \$\$ORIGIN
	QMAKE_RPATHDIR += \$\$ORIGIN/.
	RPATH = $$join( QMAKE_RPATHDIR, ":" )

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${RPATH}\'
	QMAKE_RPATHDIR =
}
