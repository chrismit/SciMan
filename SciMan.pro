#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T13:33:37
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS_DEBUG += -Wno-deprecated -Wno-unused-parameter -g
QMAKE_CXXFLAGS_RELEASE += -O3 -Wno-deprecated -Wno-unused-parameter -g

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SciMan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    task.cpp \
    taskmanager.cpp \
    gnattview.cpp

HEADERS  += mainwindow.h \
    task.h \
    taskmanager.h \
    gnattview.h

FORMS    += mainwindow.ui
