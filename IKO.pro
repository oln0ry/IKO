#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T01:16:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IKO
TEMPLATE = app


SOURCES += main.cpp\
        menu.cpp \
    mainlocator.cpp \
    indicatordrl.cpp \
    targetssettings.cpp \
    indicatorprl.cpp \
    equiangulartrianglelocator.cpp \
    righttrianglelocator.cpp \
    rspindicators.cpp

HEADERS  += menu.h \
    mainlocator.h \
    indicatordrl.h \
    targetssettings.h \
    indicatorprl.h \
    equiangulartrianglelocator.h \
    righttrianglelocator.h \
    rspindicators.h

FORMS    += menu.ui \
    indicatordrl.ui \
    targetssettings.ui \
    indicatorprl.ui \
    rspindicators.ui
