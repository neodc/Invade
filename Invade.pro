#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T20:12:58
#
#-------------------------------------------------

QT	   += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Invade
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 \
	-pedantic-errors

SOURCES += main.cpp\
	model/dicetype.cpp \
	model/phase.cpp \
	model/side.cpp \
	model/dice.cpp \
	model/unittype.cpp \
    model/position.cpp \
    model/unit.cpp \
    model/player.cpp \
    model/board.cpp \
    model/invade.cpp \
    model/effect.cpp \
    view/sujetDObservation.cpp \
    view/dicelabel.cpp \
    network/serverinvade.cpp \
    view/invadeui.cpp \
    view/newgame.cpp \
    view/elitelabel.cpp \
    view/effectlabel.cpp \
    view/clickablelabel.cpp \
    network/clientinvade.cpp

HEADERS  += \
	model/dicetype.h \
	model/phase.h \
	model/side.h \
    model/dice.h \
	model/unittype.h \
    model/position.h \
    model/unit.h \
    model/player.h \
    model/board.h \
    model/invade.h \
    model/effect.h \
    view/sujetDObservation.h \
    view/observateur.h \
    view/dicelabel.h \
    network/serverinvade.h \
    view/invadeui.h \
    view/newgame.h \
    view/elitelabel.h \
    view/effectlabel.h \
    view/clickablelabel.h \
    network/clientinvade.h

FORMS	+= invadeui.ui \
    newgame.ui \
    network/serverinvade.ui

RESOURCES += \
	resources/resources.qrc

OTHER_FILES += \
    network/listMethode.txt
