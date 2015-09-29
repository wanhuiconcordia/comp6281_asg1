TEMPLATE = app
CONFIG += console c11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    log.c \
    fileexplorer.c \
    utilities.c \
    find.c

HEADERS += \
    log.h \
    fileexplorer.h \
    find.h

