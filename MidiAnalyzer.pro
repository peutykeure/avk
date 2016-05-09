QT += core
QT += network widgets
QT -= gui

CONFIG += c++11
LIBS += -lasound
LIBS += -lpthread

DEFINES += __LINUX_ALSA__

TARGET = MidiAnalyzer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    midianalyzer.cpp \
    midievent.cpp \
    RtMidi.cpp

HEADERS += \
    midianalyzer.h \
    midievent.h \
    RtMidi.h

