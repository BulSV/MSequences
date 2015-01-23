#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T19:55:47
#
#-------------------------------------------------

QT       += core
QT       += gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG(debug, debug|release) {
    unix:DESTDIR = ../debug/SequencesGenerator/unix
    unix:OBJECTS_DIR = ../debug/SequencesGenerator/unix/objects
    unix:MOC_DIR = ../debug/SequencesGenerator/unix/moc
    unix:RCC_DIR = ../debug/SequencesGenerator/unix/moc

    win32:DESTDIR = ../debug/SequencesGenerator/win32
    win32:OBJECTS_DIR = ../debug/SequencesGenerator/win32/objects
    win32:MOC_DIR = ../debug/SequencesGenerator/win32/moc
    win32:RCC_DIR = ../debug/SequencesGenerator/win32/moc

    TARGET = SequencesGeneratorProd

#    DEFINES += DEBUG
}
else {
    unix:DESTDIR = ../release/SequencesGenerator/unix
    unix:OBJECTS_DIR = ../release/SequencesGenerator/unix/objects
    unix:MOC_DIR = ../release/SequencesGenerator/unix/moc
    unix:RCC_DIR = ../release/SequencesGenerator/unix/moc

    win32:DESTDIR = ../release/SequencesGenerator/win32
    win32:OBJECTS_DIR = ../release/SequencesGenerator/win32/objects
    win32:MOC_DIR = ../release/SequencesGenerator/win32/moc
    win32:RCC_DIR = ../release/SequencesGenerator/win32/moc

    TARGET = SequencesGeneratorPro
}

SOURCES += main.cpp \
    Generator.cpp \
    IView.cpp \
    ConsoleView.cpp

HEADERS += \
    Generator.h \
    IView.h \
    ConsoleView.h
