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
		../src/show/Event.cpp \
		../src/show/SectionToggleFadeEvent.cpp \
		../src/show/MaestroToggleRunEvent.cpp \
		../src/show/SectionSetCycleIntervalEvent.cpp \
		../src/show/SectionSetColorAnimationEvent.cpp \
		../src/show/ColorsGenerateRandomColorEvent.cpp \
		../src/show/ColorsGenerateRandomColorArrayEvent.cpp \
		../src/show/SectionSetOverlayEvent.cpp \
		../src/show/SectionUnsetOverlayEvent.cpp \
		../src/show/SectionSetPatternEvent.cpp \
		../src/show/ColorsGenerateScalingColorArrayEvent.cpp \
    demo/PatternDemo.cpp

HEADERS += mainwindow.h \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		demo/showdemo.h \
		../src/show/Event.h \
		../src/Colors.h \
		../src/Maestro.h \
		../src/Pixel.h \
		../src/Section.h \
		../src/Show.h \
		../src/Utility.h \
		../src/show/SectionToggleFadeEvent.h \
		../src/show/MaestroToggleRunEvent.h \
		../src/show/SectionSetCycleIntervalEvent.h \
		../src/show/SectionSetColorAnimationEvent.h \
		../src/show/ColorsGenerateRandomColorEvent.h \
		../src/show/ColorsGenerateRandomColorArrayEvent.h \
		../src/show/SectionSetOverlayEvent.h \
		../src/show/SectionUnsetOverlayEvent.h \
		../src/show/SectionSetPatternEvent.h \
		../src/show/ColorsGenerateScalingColorArrayEvent.h \
    demo/PatternDemo.h

FORMS	+= \
		mainwindow.ui \
		widget/maestrocontrol.ui

INCLUDEPATH += include \
			$$PWD/../src
