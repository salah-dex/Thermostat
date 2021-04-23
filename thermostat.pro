QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../common/common-header.pri)


TARGET = thermostat

include(Functionalities/functionalities.pri)

include(DataHundlers/DataHundlers.pri)

HEADERS += \
    fakethermostat.h \
    thermostat.h \



SOURCES += \
    Main.cpp \
    fakethermostat.cpp \
    thermostat.cpp
include(../../common/module.pri)

FORMS += \
    fakethermostat.ui

DISTFILES += \
    DataHundlers/DataHundlers.pri \
    Functionalities/functionalities.pri
