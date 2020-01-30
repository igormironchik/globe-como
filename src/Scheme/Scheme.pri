
RESOURCES += $$PWD/scheme_resources.qrc

HEADERS += $$PWD/enums.hpp \
           $$PWD/item_base_cfg.hpp \
           $$PWD/mm_pixels.hpp \
           $$PWD/scene.hpp \
           $$PWD/scheme_cfg.hpp \
           $$PWD/selectable.hpp \
           $$PWD/selection.hpp \
           $$PWD/size_dialog.hpp \
           $$PWD/source.hpp \
           $$PWD/source_cfg.hpp \
           $$PWD/text.hpp \
           $$PWD/text_cfg.hpp \
           $$PWD/text_dialog.hpp \
           $$PWD/view.hpp \
           $$PWD/window.hpp \
           $$PWD/window_cfg.hpp \
			$$PWD/aggregate.hpp \
			$$PWD/base_item.hpp \
			$$PWD/scheme_utils.hpp \
			$$PWD/name_dlg.hpp

SOURCES += $$PWD/item_base_cfg.cpp \
           $$PWD/mm_pixels.cpp \
           $$PWD/scene.cpp \
           $$PWD/scheme_cfg.cpp \
           $$PWD/selection.cpp \
           $$PWD/size_dialog.cpp \
           $$PWD/source.cpp \
           $$PWD/source_cfg.cpp \
           $$PWD/text.cpp \
           $$PWD/text_cfg.cpp \
           $$PWD/text_dialog.cpp \
           $$PWD/view.cpp \
           $$PWD/window.cpp \
           $$PWD/window_cfg.cpp \
			$$PWD/aggregate.cpp \
			$$PWD/selectable.cpp \
			$$PWD/base_item.cpp \
			$$PWD/scheme_utils.cpp \
			$$PWD/name_dlg.cpp

FORMS +=   $$PWD/size_dialog.ui \
           $$PWD/text_dialog.ui \
    $$PWD/name_dlg.ui
