#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T14:14:51
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxled
TEMPLATE = app


SOURCES += main.cpp\
        mxleddialog.cpp \
    mxledindicator.cpp

HEADERS  += mxleddialog.h \
    mxledindicator.h

target.path = /home/sunny

inst1.files = ./led.desktop
inst1.path = /usr/share/applications
inst2.files = ./res/images/led192.png
inst2.path = /usr/share/pixmaps

INSTALLS += target inst1 inst2

unix:!macx: LIBS += -L$$OUT_PWD/../mxdbus/ -lmxdbus

INCLUDEPATH += $$PWD/../mxdbus
DEPENDPATH += $$PWD/../mxdbus

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/libmxdbus.a

DISTFILES += \
    led.desktop
