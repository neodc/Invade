#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T20:12:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Invade
TEMPLATE = app


SOURCES += main.cpp\
        invadeui.cpp \
    phase.cpp \
    side.cpp \
    dicetype.cpp \
    model/dicetype.cpp \
    model/phase.cpp \
    model/side.cpp

HEADERS  += invadeui.h \
    phase.h \
    side.h \
    model/dicetype.h \
    model/phase.h \
    model/side.h

FORMS    += invadeui.ui
