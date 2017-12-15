TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    dbus_server.c \
    led.c

include(./config.pri)

target.path = /home/sunny
inst1.files += ../mxdbus/mxde.xml
inst1.path = /usr/share/myir
INSTALLS += target inst1

HEADERS += \
    dbus_service.h \
    led.h \
    dbus/dbus-address.h \
    dbus/dbus-arch-deps.h \
    dbus/dbus-bus.h \
    dbus/dbus-connection.h \
    dbus/dbus-errors.h \
    dbus/dbus-glib-bindings.h \
    dbus/dbus-glib-lowlevel.h \
    dbus/dbus-glib.h \
    dbus/dbus-gtype-specialized.h \
    dbus/dbus-gvalue-parse-variant.h \
    dbus/dbus-macros.h \
    dbus/dbus-memory.h \
    dbus/dbus-message.h \
    dbus/dbus-misc.h \
    dbus/dbus-pending-call.h \
    dbus/dbus-protocol.h \
    dbus/dbus-server.h \
    dbus/dbus-shared.h \
    dbus/dbus-signature.h \
    dbus/dbus-syntax.h \
    dbus/dbus-threads.h \
    dbus/dbus-types.h \
    dbus/dbus.h

