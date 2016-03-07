#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T14:45:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Labo6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    euler.cpp \
    rk.cpp \
    colorpicker.cpp \
    item.cpp \
    iteminfo.cpp \
    widget.cpp \
    pendulum.cpp

HEADERS  += mainwindow.h \
    rk.h \
    euler.h \
    colorpicker.h \
    item.h \
    iteminfo.h \
    widget.h \
    pendulum.h

FORMS    += mainwindow.ui

RESOURCES +=
