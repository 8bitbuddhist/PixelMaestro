#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T00:28:49
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = PixelMaestro_QT
TEMPLATE = app
QMAKE_CXXFLAGS = -Wunused -Wno-unused-parameter

SOURCES += main.cpp\
		drawingarea/maestrodrawingarea.cpp \
		drawingarea/simpledrawingarea.cpp \
		demo/blinkdemo.cpp \
		widget/maestrocontrol.cpp \
		controller/sectioncontroller.cpp \
		controller/maestrocontroller.cpp \
		demo/showdemo.cpp \
		../src/show/colorsgeneraterandomcolorarrayevent.cpp \
		../src/show/colorsgeneraterandomcolorevent.cpp \
		../src/show/colorsgeneratescalingcolorarrayevent.cpp \
		../src/show/event.cpp \
		../src/show/maestrotogglerunevent.cpp \
		../src/show/sectionsetcycleintervalevent.cpp \
		../src/show/sectionsetoverlayevent.cpp \
		../src/show/sectionunsetoverlayevent.cpp \
		../src/utility.cpp \
		../src/canvas/fonts/font5x8.cpp \
		../src/show/sectionsetcanvasevent.cpp \
		demo/canvasdemo.cpp \
		../src/show/canvasdrawcharevent.cpp \
		../src/show/canvasdrawtextevent.cpp \
		../src/show/canvasdrawrectevent.cpp \
		../src/show/canvasdrawlineevent.cpp \
		drawingarea/canvasdrawingarea.cpp \
		../src/show/canvasdrawcircleevent.cpp \
		../src/show/canvasdrawtriangleevent.cpp \
		../src/show/canvasdrawpointevent.cpp \
		../src/show/canvasclearevent.cpp \
		window/mainwindow.cpp \
    ../src/show/runfunctionevent.cpp \
    ../src/animation/blinkanimation.cpp \
    ../src/animation/cycleanimation.cpp \
    ../src/animation/mergeanimation.cpp \
    ../src/animation/ponganimation.cpp \
    ../src/animation/randomanimation.cpp \
    ../src/animation/solidanimation.cpp \
    ../src/animation/sparkleanimation.cpp \
    ../src/animation/waveanimation.cpp \
    ../src/animation/animation.cpp \
    ../src/show/sectionsetanimationevent.cpp \
    ../src/canvas/canvas.cpp \
    ../src/core/colors.cpp \
    ../src/core/maestro.cpp \
    ../src/core/pixel.cpp \
    ../src/core/point.cpp \
    ../src/core/section.cpp \
    ../src/show/show.cpp \
    ../src/show/animationsetfadeevent.cpp

HEADERS += \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		demo/showdemo.h \
		../src/show/colorsgeneraterandomcolorarrayevent.h \
		../src/show/colorsgeneraterandomcolorevent.h \
		../src/show/colorsgeneratescalingcolorarrayevent.h \
		../src/show/event.h \
		../src/show/maestrotogglerunevent.h \
		../src/show/sectionsetcycleintervalevent.h \
		../src/show/sectionsetoverlayevent.h \
		../src/show/sectionunsetoverlayevent.h \
		../src/utility.h \
		../src/canvas/fonts/font.h \
		../src/canvas/fonts/font5x8.h \
		../src/show/sectionsetcanvasevent.h \
		demo/canvasdemo.h \
		../src/show/canvasdrawcharevent.h \
		../src/show/canvasdrawtextevent.h \
		../src/show/canvasdrawrectevent.h \
		../src/show/canvasdrawlineevent.h \
		drawingarea/canvasdrawingarea.h \
		../src/show/canvasdrawcircleevent.h \
		../src/show/canvasdrawtriangleevent.h \
		../src/show/canvasdrawpointevent.h \
		../src/show/canvasclearevent.h \
		window/mainwindow.h \
    ../src/show/runfunctionevent.h \
    ../src/animation/blinkanimation.h \
    ../src/animation/cycleanimation.h \
    ../src/animation/mergeanimation.h \
    ../src/animation/ponganimation.h \
    ../src/animation/randomanimation.h \
    ../src/animation/solidanimation.h \
    ../src/animation/sparkleanimation.h \
    ../src/animation/waveanimation.h \
    ../src/animation/animation.h \
    ../src/show/sectionsetanimationevent.h \
    ../src/canvas/canvas.h \
    ../src/core/colors.h \
    ../src/core/maestro.h \
    ../src/core/pixel.h \
    ../src/core/point.h \
    ../src/core/section.h \
    ../src/show/animationsetfadeevent.h \
    ../src/show/show.h

FORMS	+= \
		widget/maestrocontrol.ui \
		window/mainwindow.ui

INCLUDEPATH += include \
			$$PWD/../src
