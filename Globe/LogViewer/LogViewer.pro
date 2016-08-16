
TEMPLATE = app
TARGET = LogViewer.App
DESTDIR = ../..
QT += core gui network sql widgets multimedia xml
CONFIG += windows

win32 {
    RC_FILE = log_viewer.rc
}

RESOURCES = ../Core/resources.qrc \
            log_viewer_resources.qrc

HEADERS += mainwindow.hpp \
           configuration.hpp \
           log.hpp

SOURCES += main.cpp \
           mainwindow.cpp \
           configuration.cpp \
           log.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../QtConfFile/lib \
    -L$$OUT_PWD/../../Como/lib \
    -L$$OUT_PWD/../../lib \
    -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib \
    -L$$OUT_PWD/../../QtConfFile/lib \
    -L$$OUT_PWD/../../Como/lib \
    -lQtConfFile -lComo -lGlobe.Core -lGlobe.Scheme
else:symbian: LIBS += -lGlobe.Core -lGlobe.Scheme -lQtConfFile -lComo
else:unix: LIBS += -L$$OUT_PWD/../../lib \
    -L$$OUT_PWD/../../QtConfFile/lib \
    -L$$OUT_PWD/../../Como/lib \
    -lGlobe.Core -lGlobe.Scheme -lQtConfFile -lComo

INCLUDEPATH += $$PWD/.. $$PWD/../.. $$PWD/../../QtArg $$PWD/../../Como $$PWD/../../QtConfFile
DEPENDPATH += $$PWD/.. $$PWD/../.. $$PWD/../../QtArg $$PWD/../../Como $$PWD/../../QtConfFile

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtConfFile/lib/QtConfFile.lib \
    $$OUT_PWD/../../Como/lib/Como.lib \
    $$OUT_PWD/../../lib/Globe.Core.lib \
    $$OUT_PWD/../../lib/Globe.Scheme.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtConfFile/lib/QtConfFile.lib \
    $$OUT_PWD/../../Como/lib/Como.lib \
    $$OUT_PWD/../../lib/Globe.Core.lib \
    $$OUT_PWD/../../lib/Globe.Scheme.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../QtConfFile/lib/libQtConfFile.a \
    $$OUT_PWD/../../Como/lib/libComo.a \
    $$OUT_PWD/../../lib/libGlobe.Core.a \
    $$OUT_PWD/../../lib/libGlobe.Scheme.a

include ( ../../QtArg/QtArg/qtarg.pri )
