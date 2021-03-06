TARGET = snap7-demo_internal

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ../snap7/Wrappers/c-cpp/snap7.cpp \
    main.cpp \
    s7.cpp \
    widget.cpp

HEADERS += \
    ../snap7/Wrappers/c-cpp/snap7.h \
    s7.h \
    widget.h

FORMS += \
    widget.ui

LIBS += -L$$PWD/../snap7/Windows/Win32/ -lsnap7
INCLUDEPATH += $$PWD/../snap7/Wrappers/c-cpp/

DESTDIR = $$PWD/../dist/
