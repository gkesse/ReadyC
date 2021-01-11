GRLIB = C:/Users/Admin/Downloads/Programs/ReadyLib/dev

include($$GRLIB/qtawesome/4.7.0/mingw/QtAwesome.pri)

INCLUDEPATH +=\
    $$PWD/include \

HEADERS +=\
    $$PWD/include/GInclude.h \
    $$PWD/include/GManager.h \
    $$PWD/include/GWidget.h \
    $$PWD/include/GListBox.h \
    $$PWD/include/GInsertBox.h \
    $$PWD/include/GInsertItem.h \
    $$PWD/include/GImageView.h \
    $$PWD/include/GMenu.h \
    $$PWD/include/GAddressBar.h \
    $$PWD/include/GAddressList.h \
    $$PWD/include/GWindow.h \
    $$PWD/include/GHome.h \
    $$PWD/include/GBuilder.h \
    $$PWD/include/GOpenCVUi.h \

SOURCES +=\
    $$PWD/main.cpp \
    $$PWD/manager/GManager.cpp \
    $$PWD/manager/GWidget.cpp \
    $$PWD/manager/GListBox.cpp \
    $$PWD/manager/GInsertBox.cpp \
    $$PWD/manager/GInsertItem.cpp \
    $$PWD/manager/GImageView.cpp \
    $$PWD/manager/GMenu.cpp \
    $$PWD/manager/GAddressBar.cpp \
    $$PWD/manager/GAddressList.cpp \
    $$PWD/manager/GWindow.cpp \
    $$PWD/manager/GHome.cpp \
    $$PWD/manager/GBuilder.cpp \
    $$PWD/manager/GOpenCVUi.cpp \
