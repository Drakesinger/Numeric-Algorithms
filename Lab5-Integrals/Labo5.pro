TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    functions/function.cpp \
    functions/pifunction.cpp \
    integrales/integrale.cpp \
    integrales/rectanglefixstepintegrale.cpp \
    integrales/rectanglerandomstepintegrale.cpp \
    functions/linearfunction.cpp \
    functions/sinfunction.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    functions/function.h \
    functions/pifunction.h \
    integrales/integrale.h \
    integrales/rectanglefixstepintegrale.h \
    integrales/rectanglerandomstepintegrale.h \
    functions/linearfunction.h \
    functions/sinfunction.h

