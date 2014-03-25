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
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    varCount = 4;
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
    pDrvInfo->NumDRVar = varCount;
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
    if (nWnd >= WndCount || nWnd < 0) return -1;
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
    if(nCommand >= CommandsCount || nCommand < 0) return -1;
    switch(nCommand)
    {
    case 0:
        pCommandInfo->Name = "Запрос режима вывода";//"READ_CONSTANT_MODE_F";
        pCommandInfo->Annotation = "Получение режима вывода (Вольт / Ампер / Выкл)";
        pCommandInfo->NumParam = 0;
        break;
    case 1:
        pCommandInfo->Name = "Измерить напряжение";//"MEAS_VOLTAGE_F";
        pCommandInfo->Annotation = "Запрос текущего напряжения";
        pCommandInfo->NumParam = 0;
        break;
    case 2:
        pCommandInfo->Name = "Измерить ток";//"MEAS_CURRENT_F";
        pCommandInfo->Annotation = "Запрос текущей силы тока";
        pCommandInfo->NumParam = 0;
        break;
    case 3:
        pCommandInfo->Name = "Установить напряжение";//"SET_VOLT_LIMIT_F";
        pCommandInfo->Annotation = "Установка заданного напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 4:
        pCommandInfo->Name = "Установить силу тока";//"SET_CURR_LIMIT_F";
        pCommandInfo->Annotation = "Установка заданной силы тока";
        pCommandInfo->NumParam = 1;
        break;
    case 5:
        pCommandInfo->Name = "Управление состоянием вывода";//"SET_OUTPUT_STATE_F";
        pCommandInfo->Annotation = "Вкл / выкл вывод данных";
        pCommandInfo->NumParam = 1;
        break;
    case 6:
        pCommandInfo->Name = "Установка типа управления";//"SET_SETTING_MODE_F";
        pCommandInfo->Annotation = "Локальное / Удаленное / Удаленное без отображения статуса на панели устройства";
        pCommandInfo->NumParam = 1;
        break;
    case 7:
        pCommandInfo->Name = "Установка режима запуска";//"SET_START_MODE_F";
        pCommandInfo->Annotation = "Безопасный старт / Авто перезагрузка";
        pCommandInfo->NumParam = 1;
        break;
    case 8:
        pCommandInfo->Name = "Установить верхнюю границу напряжения";//"SET_OVERVOLT_PROTECTION_F";
        pCommandInfo->Annotation = "Установить верхнюю границу напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 9:
        pCommandInfo->Name = "Установить нижнюю границу напряжения";//"SET_UNDERVOLT_LIMIT_F";
        pCommandInfo->Annotation = "Установить нижнюю границу напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 10:
        pCommandInfo->Name = "Использовать защиту с задержкой";//"SET_FOLDBACK_PROTECTION_F";
        pCommandInfo->Annotation = "Вкл / выкл режим работы с защитой";
        pCommandInfo->NumParam = 1;
        break;
    case 11:
        pCommandInfo->Name = "Установить настройки по умолчанию";//"RESET_PS_SETTINGS_F";
        pCommandInfo->Annotation = "Установить настройки по умолчанию";
        pCommandInfo->NumParam = 0;
        break;
    }
    return 0;
}

int LambdaWindow::getCommandParamInfo(int nCommand, int nParam,
                                      DrvCommandParamInfo *pCommandParamInfo)
{
    if (nCommand >= CommandsCount || nCommand < 0) return -1;
    if (nParam > 1 || nParam < 0) return 0;
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
        pCommandParamInfo->Name = "Параметр";
        pCommandParamInfo->Annotation = "Значение";
        pCommandParamInfo->Type = TYPE_DOUBLE;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 5:
    case 10:
        pCommandParamInfo->Name = "Статус";
        pCommandParamInfo->Annotation = "ВКЛ\nВЫКЛ\n";
        pCommandParamInfo->Type = TYPE_ENUM;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 6:
        pCommandParamInfo->Name = "Тип управления";
        pCommandParamInfo->Annotation = "Локальное\nУдаленное\nУдаленное без отображение на панели\n";
        pCommandParamInfo->Type = TYPE_ENUM;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 7:
        pCommandParamInfo->Name = "Режим запуска";
        pCommandParamInfo->Annotation = "Безопасный старт\nАвто перезагрузка\n";
        pCommandParamInfo->Type = TYPE_ENUM;
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
{
    if (nVar < 0 || nVar >= varCount) return -1;
    if (!lmWin) return -1;
    switch(nVar)
    {
    case 0:
        pDataVariable->Name = "Напряжение(V)";
        pDataVariable->Annotation = "Текущее напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = "Вольт";
        pDataVariable->pValue = (void*) &lmWin->voltage;
        break;
    case 1:
        pDataVariable->Name = "Сила тока(А)";
        pDataVariable->Annotation = "Текущая сила тока";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = "Ампер";
        pDataVariable->pValue = (void*) &lmWin->current;
        break;
    case 2:
        pDataVariable->Name = "Мин. Напряжение";
        pDataVariable->Annotation = "Мин. Напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = "Вольт";
        pDataVariable->pValue = (void*) &lmWin->underVoltLimit;
        break;
    case 3:
        pDataVariable->Name = "Макс. Напряжение";
        pDataVariable->Annotation = "Макс. Напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = "Вольт";
        pDataVariable->pValue = (void*) &lmWin->overVoltLimit;
        break;
    }

    return 0;
}

int LambdaWindow::makeCommand(int nCommand,
                              char *pData,
                              int nActiveObject,
                              PasportSaveValMgr *pArrayPasportSaveVal)
{
    if (nCommand < 0 || nCommand >= CommandsCount) return -1;
    switch (nCommand)
    {
    case 0:
        READ_CONSTANT_MODE_F();
        break;
    case 1:
        voltage = QString(MEAS_VOLTAGE_F());
        break;
    case 2:
        current = QString(MEAS_CURRENT_F());
        break;
    case 3:
//        double voltLimit = *((double *)pData);
        SET_VOLT_LIMIT_F(*((double *)pData));
        break;
    case 4:
//        double currLimit = *((double *)pData);
        SET_CURR_LIMIT_F(*((double *)pData));
        break;
    case 5:
//        int state = *((int*) pData);
        SET_OUTPUT_STATE_F(*((int*) pData));
        break;
    case 6:
        //int contrState = *((int*) pData);
        SET_SETTING_MODE_F(*((int*) pData));
        break;
    case 7:
//        int startState = *((int *) pData);
        SET_START_MODE_F(*((int *) pData));
        break;
    case 8:
//        double overv = *((double *) pData);
        SET_OVERVOLT_PROTECTION_F(*((double *) pData));
        overVoltLimit = QString(GET_OVERVOLT_PROTECTION_F());
        break;
    case 9:
//        double underv = *((double *) pData);
        SET_UNDERVOLT_LIMIT_F(*((double *) pData));
        underVoltLimit = QString(GET_UNDERVOLT_LIMIT_F());
        break;
    case 10:
//        int foldState = *((int *) pData);
        SET_FOLDBACK_PROTECTION_F(*((int *) pData));
        break;
    case 11:
        RESET_PS_SETTINGS_F();
        break;
    }

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
