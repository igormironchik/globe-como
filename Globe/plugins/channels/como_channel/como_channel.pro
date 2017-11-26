
TEMPLATE = lib

CONFIG += plugin

QT += core gui network

DESTDIR = ../../../../plugins/como_channel

SOURCES = plugin.cpp

unix|win32: LIBS += -L$$OUT_PWD/../../../../3rdparty/Como/lib/ \
    -L$$OUT_PWD/../../../.. \
    -lComo -lGlobe.Core

INCLUDEPATH += $$PWD/../../../../3rdparty/Como $$PWD/../../../..
DEPENDPATH += $$PWD/../../../../3rdparty/Como $$PWD/../../../..

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../../3rdparty/Como/lib/Como.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../../3rdparty/Como/lib/libComo.a

dir.commands = mkdir ../../../../plugins/como_channel

QMAKE_EXTRA_TARGETS += dir

macx {
	QMAKE_LFLAGS += -Wl,-rpath,@loader_path/../../,-rpath,@executable_path/../../
} else:linux-* {
	QMAKE_RPATHDIR += \$\$ORIGIN
	QMAKE_RPATHDIR += \$\$ORIGIN/../../
	RPATH = $$join( QMAKE_RPATHDIR, ":" )

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${RPATH}\'
	QMAKE_RPATHDIR =
}
