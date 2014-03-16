TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    timeout.c \
    hashmap.c

OTHER_FILES += \
    QtOnUbuntu(6).pdf

HEADERS += \
    timeout.h \
    hashmap.h \
    our_protocol.h

