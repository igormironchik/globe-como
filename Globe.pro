
TEMPLATE = subdirs


SUBDIRS = Como \
          QtConfFile \
          Globe

Globe.depends = Como QtConfFile
