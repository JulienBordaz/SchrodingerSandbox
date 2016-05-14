#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T19:29:57
#
#-------------------------------------------------
CONFIG += release
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SchrodingerSandbox
TEMPLATE = app

#LIBS+=-lfftw
LIBS += -LC:/FFTW2/ -lfftw3-3
#LIBS += -LC:/FFTW2/ -lfftw3f-3
#LIBS += -LC:/FFTW2/ -lfftw3l-3
INCLUDEPATH += C:/FFTW2

SOURCES += main.cpp\
        mainwindow.cpp \
    potentialdistribution.cpp \
    quantumwave.cpp \
    renderarea.cpp \
    kselectarea.cpp \
    energyselection.cpp \
    aboutdialog.cpp \
    simulationsettings.cpp \
    newsimdialog.cpp

HEADERS  += mainwindow.h \
    potentialdistribution.h \
    quantumwave.h \
    renderarea.h \
    kselectarea.h \
    energyselection.h \
    aboutdialog.h \
    simulationsettings.h \
    newsimdialog.h

FORMS    += mainwindow.ui \
    energyselection.ui \
    aboutdialog.ui \
    newsimdialog.ui
