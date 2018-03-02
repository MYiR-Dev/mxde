#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T08:59:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxsupport
TEMPLATE = app

SOURCES += main.cpp\
    mxmaindialog.cpp \
    systemactionwidget.cpp \
    systemcontentwidget.cpp


HEADERS  += \
    mxmaindialog.h \
    systemactionwidget.h \
    systemcontentwidget.h



target.path = /home/sunny

inst1.files = ./02_hello.desktop
inst1.path = /usr/share/applications
inst2.files = ./res/images/hello192.png
inst2.path = /usr/share/pixmaps

INSTALLS += target inst1 inst2
include(../mxbase/mxbase.pri)
