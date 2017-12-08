#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T02:42:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mxapp
TEMPLATE = app


SOURCES += main.cpp\
        mxmaindialog.cpp

HEADERS  += mxmaindialog.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mxdbus/release/ -lmxdbus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mxdbus/debug/ -lmxdbus
else:unix: LIBS += -L$$OUT_PWD/../mxdbus/ -lmxdbus

INCLUDEPATH += $$PWD/../mxdbus
DEPENDPATH += $$PWD/../mxdbus

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/release/libmxdbus.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/debug/libmxdbus.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/release/mxdbus.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/debug/mxdbus.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../mxdbus/libmxdbus.a
