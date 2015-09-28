TEMPLATE = app
CONFIG += console c11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    log.c \
    findandreplace.c \
    fileexplorer.c \
    utilities.c

HEADERS += \
    log.h \
    findandreplace.h \
    fileexplorer.h

