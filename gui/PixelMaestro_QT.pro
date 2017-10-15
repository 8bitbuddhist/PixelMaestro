#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T00:28:49
#
#-------------------------------------------------

QT       += core gui widgets serialport

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
		../src/canvas/fonts/font5x8.cpp \
		demo/canvasdemo.cpp \
		drawingarea/canvasdrawingarea.cpp \
		window/mainwindow.cpp \
		../src/animation/blinkanimation.cpp \
		../src/animation/cycleanimation.cpp \
		../src/animation/mergeanimation.cpp \
		../src/animation/randomanimation.cpp \
		../src/animation/solidanimation.cpp \
		../src/animation/sparkleanimation.cpp \
		../src/animation/waveanimation.cpp \
		../src/animation/animation.cpp \
		../src/core/colors.cpp \
		../src/core/maestro.cpp \
		../src/core/pixel.cpp \
		../src/core/point.cpp \
		../src/core/section.cpp \
		../src/utility.cpp \
		../src/animation/radialanimation.cpp \
		../src/animation/mandelbrotanimation.cpp \
		../src/animation/plasmaanimation.cpp \
    ../src/animation/lightninganimation.cpp \
    widget/animation/lightninganimationcontrol.cpp \
    widget/animation/plasmaanimationcontrol.cpp \
    widget/animation/sparkleanimationcontrol.cpp \
    ../src/canvas/colorcanvas.cpp \
    demo/colorcanvasdemo.cpp \
    ../src/canvas/animationcanvas.cpp \
    ../src/canvas/canvas.cpp \
    widget/canvas/canvascontrol.cpp \
    demo/cuedemo.cpp \
    ../src/cue/event.cpp \
    ../src/cue/show.cpp \
    ../src/cue/cuecontroller.cpp \
    ../src/cue/animationcuehandler.cpp \
    ../src/cue/canvascuehandler.cpp \
    ../src/cue/maestrocuehandler.cpp \
    ../src/cue/sectioncuehandler.cpp \
    window/settingsdialog.cpp \
    widget/animation/radialanimationcontrol.cpp \
    controller/palettecontroller.cpp \
    widget/palettecontrol.cpp

HEADERS += \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		demo/showdemo.h \
		../src/canvas/fonts/font.h \
		../src/canvas/fonts/font5x8.h \
		demo/canvasdemo.h \
		drawingarea/canvasdrawingarea.h \
		window/mainwindow.h \
		../src/animation/blinkanimation.h \
		../src/animation/cycleanimation.h \
		../src/animation/mergeanimation.h \
		../src/animation/randomanimation.h \
		../src/animation/solidanimation.h \
		../src/animation/sparkleanimation.h \
		../src/animation/waveanimation.h \
		../src/animation/animation.h \
		../src/core/colors.h \
		../src/core/maestro.h \
		../src/core/pixel.h \
		../src/core/point.h \
		../src/core/section.h \
		../src/utility.h \
		../src/animation/radialanimation.h \
		../src/animation/mandelbrotanimation.h \
		../src/animation/plasmaanimation.h \
    ../src/animation/lightninganimation.h \
    widget/animation/lightninganimationcontrol.h \
    widget/animation/plasmaanimationcontrol.h \
    widget/animation/sparkleanimationcontrol.h \
    ../src/canvas/colorcanvas.h \
    demo/colorcanvasdemo.h \
    ../src/canvas/canvastype.h \
    ../src/canvas/animationcanvas.h \
    ../src/canvas/canvas.h \
    widget/canvas/canvascontrol.h \
    demo/cuedemo.h \
    ../src/cue/event.h \
    ../src/cue/show.h \
    ../src/cue/cuecontroller.h \
    ../src/cue/cuehandler.h \
    ../src/cue/animationcuehandler.h \
    ../src/cue/canvascuehandler.h \
    ../src/cue/maestrocuehandler.h \
    ../src/cue/sectioncuehandler.h \
    ../src/animation/animationtype.h \
    window/settingsdialog.h \
    widget/animation/radialanimationcontrol.h \
    controller/palettecontroller.h \
    widget/palettecontrol.h

FORMS	+= \
		widget/maestrocontrol.ui \
		window/mainwindow.ui \
    widget/animation/lightninganimationcontrol.ui \
    widget/animation/plasmaanimationcontrol.ui \
    widget/animation/sparkleanimationcontrol.ui \
    widget/canvas/canvascontrol.ui \
    window/settingsdialog.ui \
    widget/animation/radialanimationcontrol.ui \
    widget/palettecontrol.ui

INCLUDEPATH += $$PWD/../src
