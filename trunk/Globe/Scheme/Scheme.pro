
TEMPLATE = lib
TARGET = Globe.Scheme
DESTDIR = ../../lib
INCLUDEPATH += . ../..
CONFIG += qt staticlib
QT += gui widgets

INCLUDEPATH += $$PWD/.. $$PWD/../..
DEPENDPATH += $$PWD/.. $$PWD/../..

HEADERS += scene.hpp \
           scheme_cfg.hpp \
           source.hpp \
           view.hpp \
           window.hpp \
           window_cfg.hpp

SOURCES += scene.cpp \
           scheme_cfg.cpp \
           source.cpp \
           view.cpp \
           window.cpp \
           window_cfg.cpp
