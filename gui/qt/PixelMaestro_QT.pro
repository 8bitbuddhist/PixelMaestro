#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T00:28:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelMaestro_QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        $$PWD/../../src/*.cpp \
        drawingarea/maestrodrawingarea.cpp \
        drawingarea/simpledrawingarea.cpp \
        demo/blinkdemo.cpp \
        widget/maestrocontrol.cpp \

HEADERS += mainwindow.h \
        demo/blinkdemo.h \
        drawingarea/maestrodrawingarea.h \
        drawingarea/simpledrawingarea.h \
        widget/maestrocontrol.h

FORMS    += \
        mainwindow.ui \
        widget/maestrocontrol.ui

INCLUDEPATH += include \
            $$PWD/../../include
