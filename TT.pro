TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += $$PWD/portaudio/include
LIBS += $$PWD/portaudio/build/libportaudio.dll.a

SOURCES += \
        Setts.cpp \
        main.cpp

HEADERS += \
    Setts.h
