
TEMPLATE = lib
TARGET = Globe.Scheme
DESTDIR = ../../lib
INCLUDEPATH += . ../..
CONFIG += qt staticlib
QT += gui widgets

INCLUDEPATH += $$PWD/.. $$PWD/../..
DEPENDPATH += $$PWD/.. $$PWD/../..

RESOURCES = scheme_resources.qrc

HEADERS += enums.hpp \
           scene.hpp \
           scheme_cfg.hpp \
           selectable.hpp \
           selection.hpp \
           source.hpp \
           view.hpp \
           window.hpp \
           window_cfg.hpp

SOURCES += scene.cpp \
           scheme_cfg.cpp \
           selection.cpp \
           source.cpp \
           view.cpp \
           window.cpp \
           window_cfg.cpp