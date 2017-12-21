#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T02:42:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxapp
TEMPLATE = app

target.path = /home/sunny/
INSTALLS += target

include(../qtsingleapplication/src/qtsingleapplication.pri)
INCLUDEPATH += $$PWD/widgets
INCLUDEPATH += $$PWD/common

SOURCES += main.cpp\
        mxmaindialog.cpp \
        mxapplication.cpp \
        homeactionwidget.cpp \
        homecontentwidget.cpp \
        boxactionwidget.cpp \
        boxcontentwidget.cpp \
        widgets/basewidget.cpp \
        widgets/shadowwidget.cpp \
        common/mxdesktopfile.cpp \
        common/mxproperties.cpp \
        common/mxlistmodel.cpp \
        common/systembutton.cpp

HEADERS  += mxmaindialog.h \
            mxapplication.h \
            homeactionwidget.h \
            homeactionwidget.h \
            homecontentwidget.h \
            boxactionwidget.h \
            boxcontentwidget.h \
            widgets/basewidget.h \
            widgets/shadowwidget.h \
            common/mxdesktopfile.h \
            common/mxproperties.h \
            common/mxlistmodel.h \
            common/systembutton.h

RESOURCES += \
    main.qrc

