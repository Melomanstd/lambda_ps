#include "lambda_plugin.h"

//Lambda_plugin::Lambda_plugin()
//{
//}

QWidget* createMainWindow()
{
    //window = new MainWindow;
    //window->hide();
    //return window;//window->centralWidget();
    return 0;
}

///-------------------------------------
LambdaWindow::LambdaWindow()
{
    lmWin = 0;
    classNum = 0;
    drvNum = 0;
    DrvName = "LambdaDrv";
    ClassName = "lambda_plugin";
    DrvAnnotation = "Lambda power supply driver";
    DrvVersion = "0.000001";
    CommandsCount = 12;
    WndCount = 1;
}

void LambdaWindow::createWindow()
{
    if (lmWin) return;
    lmWin = new MainWindow;
}

void LambdaWindow::destroyWindow()
{
    if (!lmWin) return;
    delete lmWin;
    lmWin = 0;
}

QWidget* LambdaWindow::getMainWindow()
{
    return lmWin;
}

QTranslator* LambdaWindow::getTranslator()
{
    return &lmWin->translator;
}

//--------------------------------------------------
int LambdaWindow::getInfo(DrvInfo *pDrvInfo)
{
    pDrvInfo->Number = drvNum;
    pDrvInfo->Class = classNum;
    pDrvInfo->Name = DrvName;
    pDrvInfo->NameClass = ClassName;
    pDrvInfo->Annotation = DrvAnnotation;
    pDrvInfo->Version = DrvVersion;
    pDrvInfo->NumCommand = CommandsCount;
    pDrvInfo->NumDRVar = -1;
    pDrvInfo->NumDOVar = -1;
    pDrvInfo->NumWnd = WndCount;
    pDrvInfo->bCreateProtocol = false;
    pDrvInfo->bResultWindow = false;
    pDrvInfo->bRunNoCustomTest = false;
    return 0;
}

int LambdaWindow::getWndInfo(int nWnd, DrvWndInfo *pWndInfo)
{
    if (!lmWin) return -1;
    pWndInfo->wnd = (void*) lmWin;
    pWndInfo->name = lmWin->objectName();
    pWndInfo->bShowForAdmin = true;
    pWndInfo->bShowForProgrammer = true;
    pWndInfo->bShowForUser = true;
    pWndInfo->bShowInEditMode = true;
    pWndInfo->bShowInRunMode = true;
    return 0;
}

int LambdaWindow::getCommandInfo(int nCommand, DrvCommandInfo *pCommandInfo)
{
    switch(nCommand)
    {
    case 0:
        pCommandInfo->Name = "READ_CONSTANT_MODE_F";
        pCommandInfo->Annotation = "getting constant mode";
        pCommandInfo->NumParam = 0;
        break;
    case 1:
        pCommandInfo->Name = "MEAS_VOLTAGE_F";
        pCommandInfo->Annotation = "measuring voltage level";
        pCommandInfo->NumParam = 0;
        break;
    case 2:
        pCommandInfo->Name = "MEAS_CURRENT_F";
        pCommandInfo->Annotation = "measuring current level";
        pCommandInfo->NumParam = 0;
        break;
    case 3:
        pCommandInfo->Name = "SET_VOLT_LIMIT_F";
        pCommandInfo->Annotation = "apply voltage limit";
        pCommandInfo->NumParam = 1;
        break;
    case 4:
        pCommandInfo->Name = "SET_CURR_LIMIT_F";
        pCommandInfo->Annotation = "apply current limit";
        pCommandInfo->NumParam = 1;
        break;
    case 5:
        pCommandInfo->Name = "SET_OUTPUT_STATE_F";
        pCommandInfo->Annotation = "on/off output";
        pCommandInfo->NumParam = 1;
        break;
    case 6:
        pCommandInfo->Name = "SET_SETTING_MODE_F";
        pCommandInfo->Annotation = "local / remote / same as remote";
        pCommandInfo->NumParam = 1;
        break;
    case 7:
        pCommandInfo->Name = "SET_START_MODE_F";
        pCommandInfo->Annotation = "safe start / auto restart mode";
        pCommandInfo->NumParam = 1;
        break;
    case 8:
        pCommandInfo->Name = "SET_OVERVOLT_PROTECTION_F";
        pCommandInfo->Annotation = "over-voltage protection level";
        pCommandInfo->NumParam = 1;
        break;
    case 9:
        pCommandInfo->Name = "SET_UNDERVOLT_LIMIT_F";
        pCommandInfo->Annotation = "The under-voltage limit keeps the voltage setting from being less than a certain value.";
        pCommandInfo->NumParam = 1;
        break;
    case 10:
        pCommandInfo->Name = "SET_FOLDBACK_PROTECTION_F";
        pCommandInfo->Annotation = "This command enables or disables the foldback protection. ";
        pCommandInfo->NumParam = 1;
        break;
    case 11:
        pCommandInfo->Name = "RESET_PS_SETTINGS_F";
        pCommandInfo->Annotation = "RESET_PS_SETTINGS";
        pCommandInfo->NumParam = 0;
        break;
    }
    return 0;
}

int LambdaWindow::getCommandParamInfo(int nCommand, int nParam,
                                      DrvCommandParamInfo *pCommandParamInfo)
{
    switch (nCommand)
    {
    case 0:
    case 1:
    case 2:
    case 11:
        pCommandParamInfo->Name = "";
        pCommandParamInfo->Annotation = "";
        pCommandParamInfo->Type = -1;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 3:
    case 4:
    case 8:
    case 9:
        pCommandParamInfo->Name = "val";
        pCommandParamInfo->Annotation = "some double value";
        pCommandParamInfo->Type = TYPE_DOUBLE;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    default:
        pCommandParamInfo->Name = "val";
        pCommandParamInfo->Annotation = "some int value";
        pCommandParamInfo->Type = TYPE_INT;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    }

//    if (nCommand == 0 || 1 || 2 || 11)
//    {

//    }
//    else if (nCommand == 3 || 4 || 8 || 9)
//    {

//    }
//    else
//    {

//    }
    return 0;
}

int LambdaWindow::drvOpen()
{
    createWindow();
    return 0;
}

int LambdaWindow::drvClose()
{
    destroyWindow();
    return 0;
}

QStringList LambdaWindow::commands() const
{return QStringList();}

QStringList LambdaWindow::variables() const
{return QStringList();}

int LambdaWindow::getDOInfo(int nVar, DrvVariableInfo *pDataVariable)
{return 0;}

int LambdaWindow::getDRInfo(int nVar, DrvVariableInfo *pDataVariable)
{return 0;}

int LambdaWindow::makeCommand(int nCommand,
                              char *pData,
                              int nActiveObject,
                              PasportSaveValMgr *pArrayPasportSaveVal)
{
    return 0;
}

int LambdaWindow::drvInit(DrvInitInfo *pDrvInitInfo)
{return 0;}

int LambdaWindow::drvSuspend()
{return 0;}

QString LambdaWindow::getErrorStr(int nErrorCode)
{
    return "none";
}

//--------------------------------------------------
Q_EXPORT_PLUGIN2(LambdaLib, LambdaWindow)
