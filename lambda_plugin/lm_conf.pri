
QT       += network
INCLUDEPATH += ../../plugintest/TestPlugin
#message(libsometing+aaa)
CONFIG(debug, debug|release) {
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject)
        #LIBS += $$quote($${PROJECT_PATH}/../../pluginsProject/liblibgndrv.a)
        DESTDIR = ../../bin
        LIBS += -L ../../bin/ -llm_drv
        #DEFINES += QT_NO_DEBUG_OUTPUT
}else{
        DESTDIR = ../../bin/Release
        LIBS += -L ../../bin/Release -llm_drv#../../bin/Release/liblm_drv.a
        #DESTDIR = $$quote($${PROJECT_PATH}/../../pluginsProject/Release)
        #LIBS += $$quote($${PROJECT_PATH}/../../pluginsProject/Release/liblibgndrv.a)
        #DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += ../lambda_drv \

DEFINES += LAMBDA_PLUGIN_LIBRARY

SOURCES += lambda_plugin.cpp \
    mainwindow.cpp \
    thread.cpp \
	main.cpp \
    corethread.cpp \
    timerdial.cpp

HEADERS += lambda_plugin.h\
        lambda_plugin_global.h \
    mainwindow.h \
    thread.h \
    corethread.h \
    timerdial.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

TRANSLATIONS = project_lambda_ru.ts

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc
