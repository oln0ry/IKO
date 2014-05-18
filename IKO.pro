#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T01:16:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
TARGET = IKO
TEMPLATE = app


SOURCES += main.cpp\
        menu.cpp \
    mainlocator.cpp \
    targetssettings.cpp \
    equiangulartrianglelocator.cpp \
    righttrianglelocator.cpp \
    commonview.cpp \
    indicatordrl.cpp \
    indicatorprl.cpp \
    rspindicators.cpp

HEADERS  += menu.h \
    mainlocator.h \
    targetssettings.h \
    equiangulartrianglelocator.h \
    righttrianglelocator.h \
    helper.h \
    commonview.h \
    indicatordrl.h \
    indicatorprl.h \
    rspindicators.h

FORMS    += menu.ui \
    targetssettings.ui \
    commonview.ui \
    indicatordrl.ui \
    indicatorprl.ui \
    rspindicators.ui

RESOURCES += \
    Common.qrc
