#-------------------------------------------------
#
# Project created by QtCreator 2011-05-02T08:45:22
#
#-------------------------------------------------

QT       += core gui network

TARGET = Qt-IRC-Server
TEMPLATE = app


SOURCES += main.cpp\
        serveur.cpp \
    threadserveur.cpp \
    threadconnect.cpp

HEADERS  += serveur.h \
    threadserveur.h \
    threadconnect.h

FORMS    += serveur.ui
