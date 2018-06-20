#-------------------------------------------------
#
# Project created by QtCreator 2018-06-09T19:43:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        clientwidget.cpp \
    chatthread.cpp \
    loginWidget.cpp

HEADERS  += clientwidget.h \
    chatthread.h \
    loginwidget.h

FORMS    += clientwidget.ui \
    chatthread.ui \
    loginWidget.ui


CONFIG += C++11

RESOURCES += \
    images/images.qrc
