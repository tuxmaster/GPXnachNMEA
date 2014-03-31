#-------------------------------------------------
#
# Project created by QtCreator 2014-03-30T19:35:36
#
#-------------------------------------------------

QT       += core positioning

QT       -= gui

TARGET = GPXnachNMEA
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

UI_DIR=tmp/ui
MOC_DIR=tmp/moc
OBJECTS_DIR=tmp/obj
RCC_DIR=tmp/rcc


SOURCES += Quellen/Start.cpp \
    Quellen/Haupt.cpp

HEADERS += \
    Quellen/Haupt.h \
    Quellen/Vorgaben.h
