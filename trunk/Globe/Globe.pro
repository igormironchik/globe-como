
TEMPLATE = subdirs

SUBDIRS = Core \
          Scheme \
          App

App.depends = Core Scheme
