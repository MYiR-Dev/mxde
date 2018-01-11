#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T18:20:02
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxnet
TEMPLATE = app

target.path = /home/sunny
INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += \
    mainwindow.ui
