#-------------------------------------------------
#
# Project created by QtCreator 2012-12-07T16:03:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Johnson
TEMPLATE = app


SOURCES += source/job.cpp \
    source/mashine.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/solver.cpp \
    source/ploter.cpp \
    source/solution.cpp

HEADERS  += headers/job.h \
    headers/mashine.h \
    headers/mainwindow.h \
    headers/solver.h \
    headers/dominance.h \
    headers/ploter.h \
    headers/solution.h \
    headers/node.h \
    headers/tree.h

FORMS    += ui/mainwindow.ui
