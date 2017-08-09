#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T00:28:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelMaestro_QT
TEMPLATE = app
QMAKE_CXXFLAGS = -Wunused -Wno-unused-parameter

SOURCES += main.cpp\
		mainwindow.cpp \
		$$PWD/../src/*.cpp \
		drawingarea/maestrodrawingarea.cpp \
		drawingarea/simpledrawingarea.cpp \
		demo/blinkdemo.cpp \
		widget/maestrocontrol.cpp \
		controller/sectioncontroller.cpp \
		controller/maestrocontroller.cpp \
    demo/showdemo.cpp \
    controller/showcontroller.cpp

HEADERS += mainwindow.h \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		../include/Colors.h \
		../include/Maestro.h \
		../include/Pixel.h \
		../include/Section.h \
		../include/Show.h \
		../include/Utility.h \
    demo/showdemo.h \
    controller/showcontroller.h

FORMS	+= \
		mainwindow.ui \
		widget/maestrocontrol.ui

INCLUDEPATH += include \
			$$PWD/../include
