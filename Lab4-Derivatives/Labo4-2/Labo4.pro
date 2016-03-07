#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T10:24:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
	printsupport


TARGET = Labo4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    qcustomplot.cpp \
    centralwidget.cpp \
    datawidget.cpp

HEADERS  += mainwindow.h \
    graph.h \
    qcustomplot.h \
    centralwidget.h \
    datawidget.h

FORMS    +=

RESOURCES += \
    ressources.qrc
