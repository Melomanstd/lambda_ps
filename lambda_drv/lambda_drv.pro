#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T11:27:59
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = lm_drv
TEMPLATE = lib

DEFINES += LAMBDA_DRV_LIBRARY

SOURCES += lambda_drv.cpp \
    lambdadrv.cpp

HEADERS += lambda_drv.h\
        lambda_drv_global.h \
    lambdadrv.h

CONFIG(debug, debug|release) {
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject)
        DESTDIR = ../../bin
        #DEFINES += QT_NO_DEBUG_OUTPUT
}else{
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject/Release)
        DESTDIR = ../../bin/Release
        #DEFINES += QT_NO_DEBUG_OUTPUT
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
