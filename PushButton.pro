#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T21:46:12
#
#-------------------------------------------------

QT = core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp

HEADERS  += \
    mainwindow.hpp
