QT += core gui widgets printsupport

CONFIG += qt c++11


SOURCES += \
	../../../src/AugmentationUtil.cpp \
	../../../src/ColorSpaces.cpp \
	../../../src/Augmentations.cpp \
	../../../src/ImageProcessing.cpp \
	../../../src/main.cpp \
	../../../src/qcustomplot.cpp	

HEADERS += \
    ../../../inc/AugmentationUtil.h \
    ../../../inc/ColorSpaces.h \
    ../../../inc/Augmentations.h \
    ../../../inc/ImageProcessing.h \
    ../../../inc/qcustomplot.h
    

INCLUDEPATH += ../../../lib_inc/ ../../../inc/


unix:!macx|win32: LIBS += -L$$PWD/../../../lib/linux-gcc-x64/ -lImageDSPLib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../lib/ImageDSPLib.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../lib/linux-gcc-x64/libImageDSPLib.a
