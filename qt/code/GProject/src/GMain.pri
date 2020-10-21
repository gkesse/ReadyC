GRLIB = C:/Users/Admin/Downloads/Programs/ReadyLib/dev

include($$GRLIB/qtawesome/4.7.0/mingw/QtAwesome.pri)

INCLUDEPATH +=\
    $$PWD/include \

HEADERS +=\
    $$PWD/include/GInclude.h \
    $$PWD/include/GManager.h \
    $$PWD/include/GWidget.h \
    $$PWD/include/GListBox.h \
    $$PWD/include/GAddressBar.h \
    $$PWD/include/GWindow.h \
    $$PWD/include/GHome.h \

SOURCES +=\
    $$PWD/main.cpp \
    $$PWD/manager/GManager.cpp \
    $$PWD/manager/GWidget.cpp \
    $$PWD/manager/GListBox.cpp \
    $$PWD/manager/GAddressBar.cpp \
    $$PWD/manager/GWindow.cpp \
    $$PWD/manager/GHome.cpp \