#
# for S0 by Qt
#
QT += widgets

TEMPLATE = app
TARGET = S0
#INCLUDEPATH += ..
RESOURCES = S0.qrc
#TRANSLATIONS = translations/S0_ja_JP.ts
DEFINES += DEBUG

# C++11
CONFIG += c++11

# for DEBUG
CONFIG += console

# for check spec
# message($$QMAKESPEC)

# for MinGW
win32 {
DEFINES += QWT_DLL
RC_ICONS = images/S0.ico
RC_FILE = resource/S0.rc
}

SOURCES += main.cpp

HEADERS += server.h
SOURCES += server.cpp

#INCLUDEPATH += ../libs/vpx
#LIBS += -L../libs/vpx
#LIBS += -lvpx_mingw73_x64

HEADERS += rgb2yuv/rgb2yuv.h
SOURCES += rgb2yuv/rgb2yuv.cpp

#SOURCES += rgb2yuv/rgb2yuv_v0.cpp
SOURCES += rgb2yuv/rgb2yuv_v1.cpp


