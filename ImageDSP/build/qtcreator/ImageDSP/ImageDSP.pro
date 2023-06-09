QT += core gui widgets printsupport

CONFIG += qt c++11


SOURCES += \
	../../../src/ColorSpaces.cpp \
	../../../src/ImageHistogram.cpp \
	../../../src/ImageProcessing.cpp \
	../../../src/main.cpp \
	../../../src/qcustomplot.cpp	

HEADERS += \
    ../../../inc/ColorSpaces.h \
    ../../../inc/ImageHistogram.h \
    ../../../inc/ImageProcessing.h \
    ../../../inc/qcustomplot.h
    

INCLUDEPATH += ../../../lib_inc/ ../../../inc/


unix:!macx|win32: LIBS += -L$$PWD/../../../lib/windows-mingw/ -lImageDSPLib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../lib/windows-mingw/ImageDSPLib.lib


