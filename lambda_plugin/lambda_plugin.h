#ifndef LAMBDA_PLUGIN_H
#define LAMBDA_PLUGIN_H

//#include <QObject>
//#include <QtCore>

#include "interfaces.h"
#include "interfaces2.h"
#include "mainwindow.h"
#include "lambda_plugin_global.h"

extern "C"
{
    LAMBDA_PLUGINSHARED_EXPORT QWidget* createMainWindow();
}

class LambdaWindow:public QObject, public GUIInterface/*, public DriverInterface*/
{
    Q_OBJECT
    Q_INTERFACES(GUIInterface/* DriverInterface*/)

    MainWindow *lmWin;
public:
    //-----------  gui interface
    LambdaWindow();
    void createWindow();
    void destroyWindow();
    QWidget* getMainWindow();
    QTranslator* getTranslator();

    //--------- driver interface

//    int getInfo(DrvInfo *pDrvInfo);
//    int getWndInfo(int nWnd, DrvWndInfo *pWndInfo);
//    int getCommandInfo(int nCommand, DrvCommandInfo *pCommandInfo);
//    int getCommandParamInfo(int nCommand, int nParam, DrvCommandParamInfo *pCommandParamInfo);
//    int drvOpen();
//    int drvClose();
//    QStringList commands() const;
//    QStringList variables() const;
//    int getDOInfo(int nVar, DrvVariableInfo *pDataVariable);
//    int getDRInfo(int nVar, DrvVariableInfo *pDataVariable);
//    int makeCommand(int nCommand, QByteArray &pData, int nActiveObject, PasportSaveValMgr *pArrayPasportSaveVal);
//    int drvInit(DrvInitInfo *pDrvInitInfo);
//    int drvSuspend();
//    QString getErrorStr(int nErrorCode);

//protected:
//    int classNum;
//    int drvNum;
//    int varCount;
//    QString DrvName;
//    QString ClassName;
//    QString DrvAnnotation;
//    QString DrvVersion;
//    int CommandsCount;
//    int WndCount;
};

class LAMBDA_PLUGINSHARED_EXPORT LambdaPlugin: public QObject, public DriverInterface
{
    Q_OBJECT
    Q_INTERFACES(DriverInterface)
public:
    LambdaPlugin();
    ~LambdaPlugin();

    int getInfo(DrvInfo *pDrvInfo);
    int getWndInfo(int nWnd, DrvWndInfo *pWndInfo);
    int getCommandInfo(int nCommand, DrvCommandInfo *pCommandInfo);
    int getCommandParamInfo(int nCommand, int nParam, DrvCommandParamInfo *pCommandParamInfo);
    int drvOpen(QString strAddr);
    int drvClose();
    QStringList commands() const;
    QStringList variables() const;
    int getDOInfo(int nVar, DrvVariableInfo *pDataVariable);
    int getDRInfo(int nVar, DrvVariableInfo *pDataVariable);
    int makeCommand(int nCommand, QByteArray &pData, int nActiveObject, PasportSaveValMgr *pArrayPasportSaveVal);
    int drvInit(DrvInitInfo *pDrvInitInfo);
    int drvSuspend();
    QString getErrorStr(int nErrorCode);
    int createWnd(int nWnd);
    int getCoreStatus();

    int startConndection();

protected:
    int classNum;
    int drvNum;
    int varCount;
    QString DrvName;
    QString ClassName;
    QString DrvAnnotation;
    QString DrvVersion;
    int CommandsCount;
    int WndCount;

    MainWindow *lmWin;
    CoreThread *core;
};



#endif // LAMBDA_PLUGIN_H
