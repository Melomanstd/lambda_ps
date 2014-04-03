#ifndef LAMBDA_PLUGIN_H
#define LAMBDA_PLUGIN_H

//#include <QObject>
//#include <QtCore>

#include "interfaces.h"
#include "interfaces2.h"
#include "mainwindow.h"
#include "lambda_plugin_global.h"

//class DriverInterface;
//class DrvInfo;
//class DrvCommandInfo;
//class DrvCommandParamInfo;
//class DrvVariableInfo;
//class DrvWndInfo;
//class PasportSaveValMgr;
//class DrvInitInfo;

extern "C"
{
    LAMBDA_PLUGINSHARED_EXPORT QWidget* createMainWindow();
}

class LAMBDA_PLUGINSHARED_EXPORT LambdaWindow:public QObject, public GUIInterface, public DriverInterface
{
    Q_OBJECT
    Q_INTERFACES(GUIInterface DriverInterface)

    MainWindow *lmWin;
public:
    //-----------  gui interface
    LambdaWindow();
    void createWindow();
    void destroyWindow();
    QWidget* getMainWindow();
    QTranslator* getTranslator();

    //--------- driver interface

    int getInfo(DrvInfo *pDrvInfo);
    int getWndInfo(int nWnd, DrvWndInfo *pWndInfo);
    int getCommandInfo(int nCommand, DrvCommandInfo *pCommandInfo);
    int getCommandParamInfo(int nCommand, int nParam, DrvCommandParamInfo *pCommandParamInfo);
    int drvOpen();
    int drvClose();
    QStringList commands() const;
    QStringList variables() const;
    int getDOInfo(int nVar, DrvVariableInfo *pDataVariable);
    int getDRInfo(int nVar, DrvVariableInfo *pDataVariable);
    int makeCommand(int nCommand, QByteArray &pData, int nActiveObject, PasportSaveValMgr *pArrayPasportSaveVal);
    int drvInit(DrvInitInfo *pDrvInitInfo);
    int drvSuspend();
    QString getErrorStr(int nErrorCode);

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

    //plugins variables
//    QString voltage, current;
//    QString underVoltLimit, overVoltLimit;
};

//class LAMBDA_PLUGINSHARED_EXPORT Lambda_plugin
//{
//public:
//    Lambda_plugin();
//};

#endif // LAMBDA_PLUGIN_H
