#-------------------------------------------------
#
# Project created by QtCreator 2020-02-08T20:36:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YOLOv2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

#LIBS += $$PWD/MyDLL/x64/Release/MyDLL.dll

win32:CONFIG(release, debug|release): LIBS += "-L../../TensorFlow DLL/x64/release/" -lTF

INCLUDEPATH += ../../TensorFlow DLL/TF.h
DEPENDPATH += ../../TensorFlow DLL/TF.h
