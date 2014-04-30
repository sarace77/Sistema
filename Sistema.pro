#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T14:42:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sistema
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    numbersselectorform.cpp \
    columngeneratorthread.cpp

HEADERS  += mainwindow.h \
    numbersselectorform.h \
    Defs.h \
    columngeneratorthread.h

FORMS    += mainwindow.ui \
    numbersselectorform.ui
