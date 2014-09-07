#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T12:34:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = domoticaRfSimulator
TEMPLATE = app


SOURCES += main.cpp\
        domoticasimulator.cpp \
    devices/device_slave.cpp \
    hardware/eeprom.cpp \
    hardware/ethernet.cpp \
    hardware/rf.cpp \
    hardware/sensor.cpp \
    ../../../src/devices/mrf49xa_mac.c \
    ../../../src/rfstack/client.c \
    devices/device_hardware.cpp \
    ../../../src/rfstack/packets.c \
    hardware/power.cpp \
    devices/mrf49xa_phy.cpp \
    devices/device.cpp

HEADERS  += domoticasimulator.h \
    devices/device_slave.h \
    hardware/eeprom.h \
    hardware/ethernet.h \
    hardware/rf.h \
    hardware/sensor.h \
    config.h \
    devices/device_hardware.h \
    hardware/power.h \
    devices/device.h

FORMS    += domoticasimulator.ui

INCLUDEPATH += /home/hans/Projects/Firmware/domoticaRf/inc
INCLUDEPATH += /home/hans/Projects/Firmware/domoticaRf/inc/bsp/sim
