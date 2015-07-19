#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T16:03:38
#
#-------------------------------------------------

QT       += core gui
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleshipGame
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    gamemap.cpp \
    gamecell.cpp \
    gamefields.cpp \
    fourpalubs.cpp \
    threepalubs.cpp \
    twopalubs.cpp \
    onepalub.cpp

HEADERS  += client.h \
    gamemap.h \
    gamecell.h \
    gamefields.h \
    fourpalubs.h \
    threepalubs.h \
    twopalubs.h \
    onepalub.h

FORMS    += client.ui
