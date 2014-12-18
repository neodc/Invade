#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T20:12:58
#
#-------------------------------------------------

QT	   += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Invade
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 \
	-pedantic-errors

SOURCES += main.cpp\
	invadeui.cpp \
	model/dicetype.cpp \
	model/phase.cpp \
	model/side.cpp \
	model/dice.cpp \
	model/unittype.cpp

HEADERS  += invadeui.h \
	model/dicetype.h \
	model/phase.h \
	model/side.h \
    model/dice.h \
	model/Position.h \
	model/unittype.h

FORMS	+= invadeui.ui
