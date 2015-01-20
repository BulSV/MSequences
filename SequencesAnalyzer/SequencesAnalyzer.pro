#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T08:45:43
#
#-------------------------------------------------

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG(debug, debug|release) {
    unix:DESTDIR = ../debug/SequencesAnalyzer/unix
    unix:OBJECTS_DIR = ../debug/SequencesAnalyzer/unix/objects
    unix:MOC_DIR = ../debug/SequencesAnalyzer/unix/moc
    unix:RCC_DIR = ../debug/SequencesAnalyzer/unix/moc

    win32:DESTDIR = ../debug/SequencesAnalyzer/win32
    win32:OBJECTS_DIR = ../debug/SequencesAnalyzer/win32/objects
    win32:MOC_DIR = ../debug/SequencesAnalyzer/win32/moc
    win32:RCC_DIR = ../debug/SequencesAnalyzer/win32/moc

    TARGET = SequencesAnalyzerProd   
}
else {
    unix:DESTDIR = ../release/SequencesAnalyzer/unix
    unix:OBJECTS_DIR = ../release/SequencesAnalyzer/unix/objects
    unix:MOC_DIR = ../release/SequencesAnalyzer/unix/moc
    unix:RCC_DIR = ../release/SequencesAnalyzer/unix/moc

    win32:DESTDIR = ../release/SequencesAnalyzer/win32
    win32:OBJECTS_DIR = ../release/SequencesAnalyzer/win32/objects
    win32:MOC_DIR = ../release/SequencesAnalyzer/win32/moc
    win32:RCC_DIR = ../release/SequencesAnalyzer/win32/moc

    TARGET = SequencesAnalyzerPro
}

SOURCES += main.cpp
