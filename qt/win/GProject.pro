TEMPLATE = app
TARGET = gp_c_qt
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console release gnu++11
QT += widgets
RESOURCES += resources.qrc

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \

include(../code/GProject/src/GMain.pri)
