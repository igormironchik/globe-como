
TEMPLATE = subdirs

SUBDIRS = Core \
          Scheme \
          App \
          LogViewer

App.depends = Core Scheme
LogViewer.depends = Core
