#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T12:32:30
#
#-------------------------------------------------

QT       += network

#QT       -= gui

TARGET = lm_plugin
TEMPLATE = lib

INCLUDEPATH += ../../PluginTest/TestPlugin

CONFIG(debug, debug|release) {
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject)
        #LIBS += $$quote($${PROJECT_PATH}/../../pluginsProject/liblibgndrv.a)
        DESTDIR = ../../bin
        LIBS += ../../bin/liblm_drv.a
        #DEFINES += QT_NO_DEBUG_OUTPUT
}else{
        DESTDIR = ../../bin/Release
        LIBS += ../../bin/Release/liblm_drv.a
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject/Release)
        #LIBS += $$quote($${PROJECT_PATH}/../../pluginsProject/Release/liblibgndrv.a)
        #DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += ../lambda_drv \

DEFINES += LAMBDA_PLUGIN_LIBRARY

SOURCES += lambda_plugin.cpp \
    mainwindow.cpp \
    thread.cpp

HEADERS += lambda_plugin.h\
        lambda_plugin_global.h \
    mainwindow.h \
    thread.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    mainwindow.ui
