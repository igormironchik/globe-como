
TEMPLATE = lib

CONFIG += plugin

QT += core gui network sql widgets multimedia xml

DESTDIR = ../../../../plugins/como_channel

SOURCES = plugin.cpp

unix|win32: LIBS += -L$$OUT_PWD/../../../../Como/lib/ \
    -L$$OUT_PWD/../../../../lib/ \
    -L$$OUT_PWD/../../../../QtConfFile/lib/ \
    -lComo -lQtConfFile -lGlobe.Core

INCLUDEPATH += $$PWD/../../../../Como $$PWD/../../.. $$PWD/../../../../QtConfFile
DEPENDPATH += $$PWD/../../../../Como $$PWD/../../.. $$PWD/../../../../QtConfFile

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../../Como/lib/Como.lib \
    $$OUT_PWD/../../../../lib/Globe.Core.lib \
    $$OUT_PWD/../../../../QtConfFile/lib/QtConfFile.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../../Como/lib/libComo.a \
    $$OUT_PWD/../../../../lib/libGlobe.Core.a \
    $$OUT_PWD/../../../../QtConfFile/lib/libQtConfFile.a

dir.commands = mkdir ../../../../plugins/como_channel

QMAKE_EXTRA_TARGETS += dir
