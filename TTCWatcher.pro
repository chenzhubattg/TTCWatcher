#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T20:43:42
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += testlib

QT       -= gui

TARGET = ../TTCbin/TTCWatcher
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    TCPServer.cpp \
    tcpclientsocket.cpp \
    TCPClient.cpp \
    common.cpp

HEADERS += \
    TCPServer.h \
    tcpclientsocket.h \
    TCPClient.h \
    common.h
<<<<<<< HEAD

LIBS += /usr/local/lib/libOptProgram.so
=======
>>>>>>> 8409a114d95e9278c6d5caba02f6110cdf178be1
