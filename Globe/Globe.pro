
TEMPLATE = subdirs

SUBDIRS = Core \
          App \
          plugins \
          LogViewer

App.depends = Core
LogViewer.depends = Core
