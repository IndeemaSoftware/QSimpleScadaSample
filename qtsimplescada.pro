#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T17:39:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSimpleScada
TEMPLATE = app
CONFIG +=C++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    VObject/vobject.cpp \
    VObject/vobjectinfo.cpp \
    VObject/vboard.cpp \
    VObject/vobjectinfodialog.cpp \
    VObject/vobjectinfoaxis.cpp \
    VObject/vboardcontroller.cpp \
    VObject/vboardmanager.cpp

HEADERS  += mainwindow.h \
    VObject/vobject.h \
    VObject/vobjectinfo.h \
    VObject/vboard.h \
    VObject/vobjectinfodialog.h \
    VObject/vobjectinfoaxis.h \
    VObject/vboardcontroller.h \
    VObject/vboardmanager.h \
    VObject/vboardinfo.h

FORMS    += mainwindow.ui \
    VObject/vobjectinfodialog.ui

RESOURCES += \
    resources.qrc
