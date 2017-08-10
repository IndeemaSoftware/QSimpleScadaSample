#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T17:39:42
#
#-------------------------------------------------

QT       += core gui network

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
    VSimpleScada/vobject.cpp \
    VSimpleScada/vobjectinfo.cpp \
    VSimpleScada/vboard.cpp \
    VSimpleScada/vobjectinfodialog.cpp \
    VSimpleScada/vobjectinfoaxis.cpp \
    VSimpleScada/vboardcontroller.cpp \
    VSimpleScada/vboardmanager.cpp \
    VSimpleScada/ventity/vconnecteddeviceinfo.cpp \
    VSimpleScada/ventity/vbaseprefentity.cpp \
    VSimpleScada/vdevice/vdeviceinfo.cpp

HEADERS  += mainwindow.h \
    VSimpleScada/vobject.h \
    VSimpleScada/vobjectinfo.h \
    VSimpleScada/vboard.h \
    VSimpleScada/vobjectinfodialog.h \
    VSimpleScada/vobjectinfoaxis.h \
    VSimpleScada/vboardcontroller.h \
    VSimpleScada/vboardmanager.h \
    VSimpleScada/vboardinfo.h \
    VSimpleScada/ventity/vconnecteddeviceinfo.h \
    VSimpleScada/ventity/vbaseprefentity.h \
    VSimpleScada/vdevice/vdeviceinfo.h \
    VSimpleScada/config.h

FORMS    += mainwindow.ui \
    VSimpleScada/vobjectinfodialog.ui

RESOURCES += resources.qrc
