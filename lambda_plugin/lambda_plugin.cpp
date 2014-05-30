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
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

//    varCount = 4;
    lmWin = 0;
//    classNum = 1;
//    drvNum = 1;
//    DrvName = "LambdaDrv";
//    ClassName = "lambda_plugin";
//    DrvAnnotation = "Lambda power supply driver";
//    DrvVersion = "0.000001";
//    CommandsCount = 12;
//    WndCount = 1;
}

void LambdaWindow::createWindow()
{
    if (lmWin) return;
    lmWin = new MainWindow;
}

void LambdaWindow::destroyWindow()
{
    if (!lmWin) return;
    closeSocket();
    delete lmWin;
    lmWin = 0;
}

QWidget* LambdaWindow::getMainWindow()
{
    return 0;//lmWin;
}

QTranslator* LambdaWindow::getTranslator()
{
    return 0;//&lmWin->translator;
}

//--------------------------------------------------


//--------------------------------------------------
LambdaPlugin::LambdaPlugin()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    varCount = 4;
    lmWin = 0;
    core = 0;
    classNum = 1;
    drvNum = 1;
    DrvName = "LambdaDrv";
    ClassName = "lambda_plugin";
    DrvAnnotation = "Lambda power supply driver";
    DrvVersion = "0.000001";
    CommandsCount = 12;
    WndCount = 1;
}

LambdaPlugin::~LambdaPlugin()
{}

int LambdaPlugin::getInfo(DrvInfo *pDrvInfo)
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

int LambdaPlugin::getWndInfo(int nWnd, DrvWndInfo *pWndInfo)
{
//    if (!lmWin) return -1;
    if (nWnd >= WndCount || nWnd < 0) return -1;
    pWndInfo->wnd = (void*) lmWin;
    pWndInfo->name = tr("Lambda");//lmWin->objectName();
    pWndInfo->bShowForAdmin = true;
    pWndInfo->bShowForProgrammer = true;
    pWndInfo->bShowForUser = true;
    pWndInfo->bShowInEditMode = true;
    pWndInfo->bShowInRunMode = true;
    return 0;
}

int LambdaPlugin::getCommandInfo(int nCommand, DrvCommandInfo *pCommandInfo)
{
    if(nCommand >= CommandsCount || nCommand < 0) return -1;
    switch(nCommand)
    {
    case 0:
        pCommandInfo->Name = tr("Output mode");//"Режима вывода";//"READ_CONSTANT_MODE_F";
        pCommandInfo->Annotation = tr("Output mode a");//"Получение режима вывода (Вольт / Ампер / Выкл)";
        pCommandInfo->NumParam = 0;
        break;
    case 1:
        pCommandInfo->Name = tr("Meas Voltage");//"Измерить напряжение";//"MEAS_VOLTAGE_F";
        pCommandInfo->Annotation = tr("Meas Voltage a");//"Запрос текущего напряжения";
        pCommandInfo->NumParam = 0;
        break;
    case 2:
        pCommandInfo->Name = tr("Meas Current");//"Измерить ток";//"MEAS_CURRENT_F";
        pCommandInfo->Annotation = tr("Meas Current a");//"Запрос текущей силы тока";
        pCommandInfo->NumParam = 0;
        break;
    case 3:
        pCommandInfo->Name = tr("Set Volt Limit");//"Установить напряжение";//"SET_VOLT_LIMIT_F";
        pCommandInfo->Annotation = tr("Set Volt Limit a");//"Установка заданного напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 4:
        pCommandInfo->Name = tr("Set Curr Limit");//"Установить силу тока";//"SET_CURR_LIMIT_F";
        pCommandInfo->Annotation = tr("Set Curr Limit a");//"Установка заданной силы тока";
        pCommandInfo->NumParam = 1;
        break;
    case 5:
        pCommandInfo->Name = tr("Output State");//"Состояние вывода";//"SET_OUTPUT_STATE_F";
        pCommandInfo->Annotation = tr("Output State a");//"Вкл / выкл вывод данных";
        pCommandInfo->NumParam = 1;
        break;
    case 6:
        pCommandInfo->Name = tr("Set Control Mode");//"Установить тип управления";//"SET_SETTING_MODE_F";
        pCommandInfo->Annotation = tr("Set Control Mode a");//"Локальное / Удаленное / Удаленное без отображения статуса на панели устройства";
        pCommandInfo->NumParam = 1;
        break;
    case 7:
        pCommandInfo->Name = tr("Set Start Mode");//"Установить режим запуска";//"SET_START_MODE_F";
        pCommandInfo->Annotation = tr("Set Start Mode a");//"Безопасный старт / Авто перезагрузка";
        pCommandInfo->NumParam = 1;
        break;
    case 8:
        pCommandInfo->Name = tr("Set Overvolt Protection");//"Установить верхнюю границу напряжения";//"SET_OVERVOLT_PROTECTION_F";
        pCommandInfo->Annotation = tr("Set Overvolt Protection a");//"Установить верхнюю границу напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 9:
        pCommandInfo->Name = tr("Set Undervolt Limit");//"Установить нижнюю границу напряжения";//"SET_UNDERVOLT_LIMIT_F";
        pCommandInfo->Annotation = tr("Set Undervolt Limit a");//"Установить нижнюю границу напряжения";
        pCommandInfo->NumParam = 1;
        break;
    case 10:
        pCommandInfo->Name = tr("Set Folback Protection");//"Использовать защиту с задержкой";//"SET_FOLDBACK_PROTECTION_F";
        pCommandInfo->Annotation = tr("Set Folback Protection a");//"Вкл / выкл режим работы с защитой";
        pCommandInfo->NumParam = 1;
        break;
    case 11:
        pCommandInfo->Name = tr("Reset");//"Сброс";//"RESET_PS_SETTINGS_F";
        pCommandInfo->Annotation = tr("Reset a");"Установить настройки по умолчанию";
        pCommandInfo->NumParam = 0;
        break;
    case 12:
        pCommandInfo->Name = tr("Connect");//"Установить соеденение";//"RESET_PS_SETTINGS_F";
        pCommandInfo->Annotation = tr("Connect a");//"Установить соеденение с источником питания";
        pCommandInfo->NumParam = 0;
        break;
    }
    return 0;
}

int LambdaPlugin::getCommandParamInfo(int nCommand, int nParam,
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
        pCommandParamInfo->Name = tr("Parameter");
        pCommandParamInfo->Annotation = tr("Parameter");
        pCommandParamInfo->Type = TYPE_DOUBLE;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 5:
    case 10:
        pCommandParamInfo->Name = tr("Status");
        pCommandParamInfo->Annotation = tr("OFF\nON\n");
        pCommandParamInfo->Type = TYPE_ENUM;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 6:
        pCommandParamInfo->Name = tr("Control Mode");//"Тип управления";
        pCommandParamInfo->Annotation = tr("Local\nRemote\nSilent Remote\n");
        pCommandParamInfo->Type = TYPE_ENUM;
        pCommandParamInfo->LRange = 0;
        pCommandParamInfo->RRange = 0;
        break;
    case 7:
        pCommandParamInfo->Name = tr("Start Mode");
        pCommandParamInfo->Annotation = tr("Safe Statr\nAuto Restart\n");
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

int LambdaPlugin::drvOpen(QString strAddr)
{

//    createWindow();
//    openSocket("192.168.1.103", "8003");
//    SET_OUTPUT_STATE_F(1);
    if(core) return -1;
    QStringList address = strAddr.split("::");
    core = new CoreThread;
    if (address.size()!=4) return -3;
    core->startThread(address.at(1), address.at(2));


//    core->start();
    return 0;
}

int LambdaPlugin::drvClose()
{
//    closeSocket();
//    destroyWindow();
    if (!core) return -1;
    core->stopThread();
    core->wait(1000);
    delete core;
    core = 0;
    return 0;
}

QStringList LambdaPlugin::commands() const
{return QStringList();}

QStringList LambdaPlugin::variables() const
{return QStringList();}

int LambdaPlugin::getDOInfo(int nVar, DrvVariableInfo *pDataVariable)
{return 0;}

int LambdaPlugin::getDRInfo(int nVar, DrvVariableInfo *pDataVariable)
{
    if (nVar < 0 || nVar >= varCount) return -1;
//    if (!core) return -1;
    switch(nVar)
    {
    case 0:
        pDataVariable->Name = tr("U");
        pDataVariable->Annotation = tr("Voltage a");//"Текущее напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = tr("V");
        pDataVariable->pValue = (void*) &core->voltage;
        break;
    case 1:
        pDataVariable->Name = tr("I");
        pDataVariable->Annotation = tr("Current a");//"Текущая сила тока";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = tr("A");
        pDataVariable->pValue = (void*) &core->current;
        break;
    case 2:
        pDataVariable->Name = tr("Umin");
        pDataVariable->Annotation = tr("min Volt a");//"Мин. Напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = tr("V");
        pDataVariable->pValue = (void*) &core->uVolt;
        break;
    case 3:
        pDataVariable->Name = tr("Umax");
        pDataVariable->Annotation = tr("max Volt a");//"Макс. Напряжение";
        pDataVariable->Type = TYPE_DOUBLE;
        pDataVariable->ED = tr("V");
        pDataVariable->pValue = (void*) &core->oVolt;
        break;
    }
    return 0;
}

int LambdaPlugin::makeCommand(int nCommand,
                              QByteArray &pData,
                              int nActiveObject,
                              PasportSaveValMgr *pArrayPasportSaveVal)
{
    if (nCommand < 0 || nCommand >= CommandsCount) return -1;
//    openSocket("192.168.1.103", "8003");
    QDataStream data(pData);
    qreal t1=0;
    quint8 t2 = 0;
    switch (nCommand)
    {
    case 0:
        READ_CONSTANT_MODE_F();
        break;
    case 1:
//        voltage = QString(MEAS_VOLTAGE_F());
        break;
    case 2:
//        current = QString(MEAS_CURRENT_F());
        break;
    case 3:
//        double voltLimit = *((double *)pData);
        t1=0;
        data>>t1;
        SET_VOLT_LIMIT_F(t1);//*((double *)pData));
        break;
    case 4:
//        double currLimit = *((double *)pData);
        t1=0;
        data>>t1;
        SET_CURR_LIMIT_F(t1);//*((double *)pData));
        break;
    case 5:
//        int state = *((int*) pData);
        t2=0;
        data>>t2;
        SET_OUTPUT_STATE_F(t2);//*((int*) pData));
        break;
    case 6:
        //int contrState = *((int*) pData);
        t2=0;
        data>>t2;
        SET_SETTING_MODE_F(t2);//*((int*) pData));
        break;
    case 7:
//        int startState = *((int *) pData);
        t2=0;
        data>>t2;
        SET_START_MODE_F(t2);//*((int *) pData));
        break;
    case 8:
//        double overv = *((double *) pData);
        t1=0;
        data>>t1;
        SET_OVERVOLT_PROTECTION_F(t1);//*((double *) pData));
//        overVoltLimit = QString(GET_OVERVOLT_PROTECTION_F());
        break;
    case 9:
//        double underv = *((double *) pData);
        t1=0;
        data>>t1;
        SET_UNDERVOLT_LIMIT_F(t1);//*((double *) pData));
//        underVoltLimit = QString(GET_UNDERVOLT_LIMIT_F());
        break;
    case 10:
//        int foldState = *((int *) pData);
        t2=0;
        data>>t2;
        SET_FOLDBACK_PROTECTION_F(t2);//*((int *) pData));
        break;
    case 11:
        RESET_PS_SETTINGS_F();
        break;
    case 12:
        startConndection();
        break;
    }

//    closeSocket();
    return 0;
}

int LambdaPlugin::drvInit(DrvInitInfo *pDrvInitInfo)
{
    if (!lmWin || !core) return -1;
    lmWin->setEnabled(false);
    RESET_PS_SETTINGS_F();
//    core->start();
    return 0;
}

int LambdaPlugin::drvSuspend()
{
    if(!lmWin || !core) return -1;
    lmWin->setEnabled(true);
    RESET_PS_SETTINGS_F();
//    core->stopThread();
    return 0;
}

QString LambdaPlugin::getErrorStr(int nErrorCode)
{
    return "none";
}

int LambdaPlugin::createWnd(int nWnd)
{
//    DrvWndInfo temp;
//    getWndInfo(nWnd,&temp);
//    return -1;
    if (lmWin || !core) return -1;
    if (nWnd<0 || nWnd > WndCount) return -2;
    switch (nWnd)
    {
    case 0:
        lmWin = new MainWindow(core, true);
        lmWin->hide();
        break;
    }
    return 0;
}

int LambdaPlugin::getCoreStatus()
{
    if(!core) return -1;
    return !core->connected;
}

int LambdaPlugin::startConndection()
{
    if (!core) return -1;
    if (core->isRunning()) return -2;
    core->start();
    return 0;
}

//--------------------------------------------------
Q_EXPORT_PLUGIN2(LambdaLib, LambdaPlugin)
