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
		drawingarea/maestrodrawingarea.cpp \
		drawingarea/simpledrawingarea.cpp \
		demo/blinkdemo.cpp \
		widget/maestrocontrol.cpp \
		controller/sectioncontroller.cpp \
		controller/maestrocontroller.cpp \
		demo/showdemo.cpp \
		demo/patterndemo.cpp \
		../src/show/colorsgeneraterandomcolorarrayevent.cpp \
		../src/show/colorsgeneraterandomcolorevent.cpp \
		../src/show/colorsgeneratescalingcolorarrayevent.cpp \
		../src/show/event.cpp \
		../src/show/maestrotogglerunevent.cpp \
		../src/show/sectionsetcoloranimationevent.cpp \
		../src/show/sectionsetcycleintervalevent.cpp \
		../src/show/sectionsetoverlayevent.cpp \
		../src/show/sectionsetpatternevent.cpp \
		../src/show/sectiontogglefadeevent.cpp \
		../src/show/sectionunsetoverlayevent.cpp \
		../src/colors.cpp \
		../src/maestro.cpp \
		../src/pixel.cpp \
		../src/section.cpp \
		../src/show.cpp \
		../src/utility.cpp \
		../src/pattern/fontutil.cpp \
		../src/pattern/fonts/font5x8.cpp \
		../src/point.cpp \
    ../src/pattern.cpp

HEADERS += mainwindow.h \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		demo/showdemo.h \
		demo/patterndemo.h \
		../src/show/colorsgeneraterandomcolorarrayevent.h \
		../src/show/colorsgeneraterandomcolorevent.h \
		../src/show/colorsgeneratescalingcolorarrayevent.h \
		../src/show/event.h \
		../src/show/maestrotogglerunevent.h \
		../src/show/sectionsetcoloranimationevent.h \
		../src/show/sectionsetcycleintervalevent.h \
		../src/show/sectionsetoverlayevent.h \
		../src/show/sectionsetpatternevent.h \
		../src/show/sectiontogglefadeevent.h \
		../src/show/sectionunsetoverlayevent.h \
		../src/colors.h \
		../src/maestro.h \
		../src/pixel.h \
		../src/section.h \
		../src/show.h \
		../src/utility.h \
		../src/pattern/fonts/font5x8.h \
		../src/pattern/fontutil.h \
		../src/pattern/fonts/font.h \
		../src/point.h \
    ../src/pattern.h

FORMS	+= \
		mainwindow.ui \
		widget/maestrocontrol.ui

INCLUDEPATH += include \
			$$PWD/../src
