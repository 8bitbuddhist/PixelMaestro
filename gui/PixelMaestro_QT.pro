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
		controller/showcontroller.cpp \
		../src/show/Transition.cpp \
		../src/show/SectionToggleFadeTransition.cpp \
		../src/show/MaestroToggleRunTransition.cpp \
		../src/show/SectionSetCycleIntervalTransition.cpp \
    ../src/show/SectionSetColorAnimationTransition.cpp \
    ../src/show/ColorsGenerateRandomColorTransition.cpp \
    ../src/show/ColorsGenerateScalingColorArray.cpp \
    ../src/show/ColorsGenerateRandomColorArrayTransition.cpp

HEADERS += mainwindow.h \
		demo/blinkdemo.h \
		drawingarea/maestrodrawingarea.h \
		drawingarea/simpledrawingarea.h \
		widget/maestrocontrol.h \
		controller/sectioncontroller.h \
		controller/maestrocontroller.h \
		demo/showdemo.h \
		controller/showcontroller.h \
		../src/show/Transition.h \
		../src/Colors.h \
		../src/Maestro.h \
		../src/Pixel.h \
		../src/Section.h \
		../src/Show.h \
		../src/Utility.h \
		../src/show/SectionToggleFadeTransition.h \
		../src/show/MaestroToggleRunTransition.h \
		../src/show/SectionSetCycleIntervalTransition.h \
    ../src/show/SectionSetColorAnimationTransition.h \
    ../src/show/ColorsGenerateRandomColorTransition.h \
    ../src/show/ColorsGenerateScalingColorArray.h \
    ../src/show/ColorsGenerateRandomColorArrayTransition.h

FORMS	+= \
		mainwindow.ui \
		widget/maestrocontrol.ui

INCLUDEPATH += include \
			$$PWD/../src
