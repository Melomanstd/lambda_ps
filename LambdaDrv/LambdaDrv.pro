#-------------------------------------------------
#
# Project created by QtCreator 2014-03-14T15:45:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LambdaDrv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lambdadrv.cpp

HEADERS  += mainwindow.h \
    lambdadrv.h

#INCLUDEPATH += ../../generator/generator_plugin
FORMS    += mainwindow.ui
