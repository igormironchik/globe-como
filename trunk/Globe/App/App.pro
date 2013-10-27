
TEMPLATE = app
TARGET = Globe
DESTDIR = ../..
QT += core gui network sql widgets multimedia
CONFIG += console

win32 {
    RC_FILE = globe.rc
}

RESOURCES = ../Core/resources.qrc

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme
else:symbian: LIBS += -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme
else:unix: LIBS += -L$$OUT_PWD/../../lib -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme

INCLUDEPATH += $$PWD/.. $$PWD/../..
DEPENDPATH += $$PWD/.. $$PWD/../..

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/QtConfFile.lib $$OUT_PWD/../../lib/Como.lib $$OUT_PWD/../../lib/Globe.Core.lib $$OUT_PWD/../../lib/Globe.Scheme.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/QtConfFile.lib $$OUT_PWD/../../lib/Como.lib $$OUT_PWD/../../lib/Globe.Core.lib $$OUT_PWD/../../lib/Globe.Scheme.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../lib/libQtConfFile.a $$OUT_PWD/../../lib/libComo.a $$OUT_PWD/../../lib/Globe.Core.a $$OUT_PWD/../../lib/Globe.Scheme.a

include ( ../../QtArg/qtarg.pri )
