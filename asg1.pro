TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    log.c \
    fileExplorer.c \
    tools.c \
    findandreplace.c

HEADERS += \
    log.h \
    fileExplorer.h \
    tools.h \
    findandreplace.h

