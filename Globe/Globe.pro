
TEMPLATE = subdirs

SUBDIRS = Core \
          Scheme \
          App \
	  plugins \
          LogViewer

App.depends = Core Scheme
LogViewer.depends = Core
