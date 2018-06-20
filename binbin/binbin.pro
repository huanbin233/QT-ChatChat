#-------------------------------------------------
#
# Project created by QtCreator 2018-06-09 T16:42:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = binbin
TEMPLATE = app


SOURCES += main.cpp\
        tcpserver.cpp \
    childthread.cpp

HEADERS  += tcpserver.h \
    childthread.h

FORMS    += tcpserver.ui

CONFIG+= C++11
