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
    indicatorprl.cpp \
    equiangulartrianglelocator.cpp \
    righttrianglelocator.cpp \
    rspindicators.cpp \
    commonview.cpp \
    indicatordrl.cpp

HEADERS  += menu.h \
    mainlocator.h \
    targetssettings.h \
    indicatorprl.h \
    equiangulartrianglelocator.h \
    righttrianglelocator.h \
    rspindicators.h \
    helper.h \
    commonview.h \
    indicatordrl.h

FORMS    += menu.ui \
    targetssettings.ui \
    indicatorprl.ui \
    rspindicators.ui \
    commonview.ui \
    indicatordrl.ui

RESOURCES += \
    Common.qrc
