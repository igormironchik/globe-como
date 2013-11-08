
TEMPLATE = lib
TARGET = Globe.Scheme
DESTDIR = ../../lib
INCLUDEPATH += . ../..
CONFIG += qt staticlib
QT += gui widgets sql

INCLUDEPATH += $$PWD/.. $$PWD/../..
DEPENDPATH += $$PWD/.. $$PWD/../..

RESOURCES = scheme_resources.qrc

HEADERS += enums.hpp \
           item_base_cfg.hpp \
           mm_pixels.hpp \
           scene.hpp \
           scheme_cfg.hpp \
           selectable.hpp \
           selection.hpp \
           size_dialog.hpp \
           source.hpp \
           source_cfg.hpp \
           view.hpp \
           window.hpp \
           window_cfg.hpp

SOURCES += item_base_cfg.cpp \
           mm_pixels.cpp \
           scene.cpp \
           scheme_cfg.cpp \
           selection.cpp \
           size_dialog.cpp \
           source.cpp \
           source_cfg.cpp \
           view.cpp \
           window.cpp \
           window_cfg.cpp

FORMS +=   size_dialog.ui
