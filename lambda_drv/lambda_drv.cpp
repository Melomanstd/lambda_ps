#include "lambda_drv.h"
#include <QDebug>

//Lambda_drv::Lambda_drv()
//{
//}

LambdaDrv *drv = 0;

int openSocket(char *ip, char *port)
{
    if(drv) return -1;
    drv = new LambdaDrv;
    return drv->openSocket(QString(ip), QString(port));
}

int closeSocket()
{
    if (!drv) return -1;
    drv->closeSocket();
    delete drv;
    drv = 0;
    return 0;
}

//---------------------------

char* FIRMWARE_REVISION_F()
{
    if(!drv) return '\0';
    QString str = drv->FIRMWARE_REVISION_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_VOLT_LIMIT_F(double val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_VOLT_LIMIT_F(val);
}

char* GET_VOLT_LIMIT_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_VOLT_LIMIT_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_CURR_LIMIT_F(double val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_CURR_LIMIT_F(val);
}

char* GET_CURR_LIMIT_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_CURR_LIMIT_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_OUTPUT_STATE_F(int val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_OUTPUT_STATE_F(val);
}

char* GET_OUTPUT_STATE_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_OUTPUT_STATE_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* MEAS_VOLTAGE_F()
{
    if(!drv) return '\0';
    QString str = drv->MEAS_VOLTAGE_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* MEAS_CURRENT_F()
{
    if(!drv) return '\0';
    QString str = drv->MEAS_CURRENT_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* READ_CONSTANT_MODE_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_CONSTANT_MODE_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_SETTING_MODE_F(int val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_SETTING_MODE_F(val);
}

char* GET_SETTING_MODE_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_SETTING_MODE_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_START_MODE_F(int val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_START_MODE_F(val);
}

char* GET_START_MODE_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_START_MODE_F();
    QByteArray res = str.toAscii();
    return res.data();
}


int SET_OVERVOLT_PROTECTION_F(double val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_OVERVOLT_PROTECTION_F(val);
}

char* GET_OVERVOLT_PROTECTION_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_OVERVOLT_PROTECTION_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* READ_OVERVOLT_TRIPPED_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_OVERVOLT_TRIPPED_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_UNDERVOLT_LIMIT_F(double val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_UNDERVOLT_LIMIT_F(val);
}

char* GET_UNDERVOLT_LIMIT_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_UNDERVOLT_LIMIT_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_FOLDBACK_PROTECTION_F(int val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_FOLDBACK_PROTECTION_F(val);
}

char* GET_FOLDBACK_PROTECTION_F()
{
    if(!drv) return '\0';
    QString str = drv->GET_FOLDBACK_PROTECTION_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* READ_FOLDBACK_TRIPPED_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_FOLDBACK_TRIPPED_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int SET_LAN_LED_STATE_F(int val)
{
    if(!drv) return -1;
//    checkForErrors();
//    readData(msg);
    return drv->SET_LAN_LED_STATE_F(val);
}

char* READ_HOSTNAME_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_HOSTNAME_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* READ_IP_ADDRESS_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_IP_ADDRESS_F();
    QByteArray res = str.toAscii();
    return res.data();
}

char* READ_MAC_ADDRESS_F()
{
    if(!drv) return '\0';
    QString str = drv->READ_MAC_ADDRESS_F();
    QByteArray res = str.toAscii();
    return res.data();
}

int RESET_LAN_SETTINGS_F()
{
    if(!drv) return -1;
//    writeData("SYST:COMM:LAN:RES");
//    QByteArray msg; msg.resize(64);
//    readData(msg);
    return drv->RESET_LAN_SETTINGS_F();
}

int RESET_PS_SETTINGS_F()
{
    if(!drv) return -1;
//    writeData("*RST");
    return drv->RESET_PS_SETTINGS_F();
}

int SAVE_PS_SETTINGS_F()
{
    if(!drv) return -1;
//    writeData("*SAV 0");
    return drv->SAVE_PS_SETTINGS_F();
}

int RECALL_PS_SETTINGS_F()
{
    if(!drv) return -1;
//    writeData("*RCL 0");
    return drv->RECALL_PS_SETTINGS_F();
}

int SELF_TEST_F()
{
    if(!drv) return -1;
//    writeData("*TST ?");
    return drv->SELF_TEST_F();
}
