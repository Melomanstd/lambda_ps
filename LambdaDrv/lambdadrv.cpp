#include "lambdadrv.h"
#include <QDebug>

LambdaDrv::LambdaDrv(QObject *parent) :
    QObject(parent)
{
    tcpSocket = 0;
}

LambdaDrv::~LambdaDrv()
{
    if(tcpSocket)
        closeSocket();
}

int LambdaDrv::openSocket(QString ip, QString port)
{
    if (tcpSocket) return -1;
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress(ip),port.toInt());
//    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSomething()));
    return 0;
}

int LambdaDrv::closeSocket()
{
    if (!tcpSocket) return -1;
    tcpSocket->close();
    return 0;
}

void LambdaDrv::writeData(QString query)
{
    if (!tcpSocket || !tcpSocket->isOpen()) return;
    QByteArray q = query.toAscii();
    qDebug()<<"sended: "<<QString(q);
    tcpSocket->write(q.data());
}

void LambdaDrv::readData(QByteArray &msg)
{
    if (!tcpSocket || !tcpSocket->isOpen()) return;
//    msg = tcpSocket->read(64);
    if(tcpSocket->waitForReadyRead(1000))
    {
        msg = tcpSocket->read(msg.size());
//        msg.trimmed();
        qDebug()<<"";
    }
    else msg.clear();
}

void LambdaDrv::checkForErrors()
{
//    writeData("SYST:ERR:ENAB");
    writeData("SYST:ERR?");
    QByteArray msg; msg.resize(64);
    readData(msg);
}

QString LambdaDrv::FIRMWARE_REVISION_F()
{
    writeData("*IDN?");
    QByteArray msg; msg.resize(64);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_VOLT_LIMIT_F(double val)
{
    QString query =":VOLT " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_VOLT_LIMIT_F()
{
    writeData(":VOLT?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_CURR_LIMIT_F(double val)
{
    QString query =":CURR " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_CURR_LIMIT_F()
{
    writeData(":CURR?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_OUTPUT_STATE_F(int val)
{
    QString query ="OUTP:STAT " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_OUTPUT_STATE_F()
{
    writeData("OUTP:STAT?");
    QByteArray msg; msg.resize(32);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::MEAS_VOLTAGE_F()
{
    writeData("MEAS:VOLT?");
    QByteArray msg; msg.resize(16);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::MEAS_CURRENT_F()
{
    writeData("MEAS:CURR?");
    QByteArray msg; msg.resize(16);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::READ_CONSTANT_MODE_F()
{
    writeData("SOUR:MOD?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_SETTING_MODE_F(int val)
{
    QString query ="SYST:SET " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_SETTING_MODE_F()
{
    writeData("SYST:SET?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_START_MODE_F(int val)
{
    QString query ="OUTP:PON " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_START_MODE_F()
{
    writeData("OUTP:PON?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}


int LambdaDrv::SET_OVERVOLT_PROTECTION_F(double val)
{
    QString query =":VOLT:PROT:LEV " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_OVERVOLT_PROTECTION_F()
{
    writeData(":VOLT:PROT:LEV?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::READ_OVERVOLT_TRIPPED_F()
{
    writeData(":VOLT :PROT :TRIP?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_UNDERVOLT_LIMIT_F(double val)
{
    QString query =":VOLT:LIM:LOW " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_UNDERVOLT_LIMIT_F()
{
    writeData(":VOLT:LIM:LOW?");
    QByteArray msg; msg.resize(8);
    readData(msg);
//    double t=msg.toDouble();
    return QString(msg);
}

int LambdaDrv::SET_FOLDBACK_PROTECTION_F(int val)
{
    QString query =":CURR:PROT:STAT " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::GET_FOLDBACK_PROTECTION_F()
{
    writeData(":CURR:PROT:STAT?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::READ_FOLDBACK_TRIPPED_F()
{
    writeData(":CURR:PROT:TRIP?");
    QByteArray msg; msg.resize(8);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::SET_LAN_LED_STATE_F(int val)
{
    QString query =":SYST:COMM:LAN:IDLED " + QString::number(val);
    writeData(query);
    QByteArray msg; msg.resize(32);
//    checkForErrors();
//    readData(msg);
    return 0;
}

QString LambdaDrv::READ_HOSTNAME_F()
{
    writeData("SYST:COMM:LAN:HOST?");
    QByteArray msg; msg.resize(64);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::READ_IP_ADDRESS_F()
{
    writeData("SYST:COMM:LAN:IP?");
    QByteArray msg; msg.resize(64);
    readData(msg);
    return QString(msg);
}

QString LambdaDrv::READ_MAC_ADDRESS_F()
{
    writeData("SYST:COMM:LAN:MAC?");
    QByteArray msg; msg.resize(64);
    readData(msg);
    return QString(msg);
}

int LambdaDrv::RESET_LAN_SETTINGS_F()
{
    writeData("SYST:COMM:LAN:RES");
//    QByteArray msg; msg.resize(64);
//    readData(msg);
    return 0;
}

int LambdaDrv::RESET_PS_SETTINGS_F()
{
    writeData("*RST");
    return 0;
}

int LambdaDrv::SAVE_PS_SETTINGS_F()
{
    writeData("*SAV 0");
    return 0;
}

int LambdaDrv::RECALL_PS_SETTINGS_F()
{
    writeData("*RCL 0");
    return 0;
}

int LambdaDrv::SELF_TEST_F()
{
    writeData("*TST ?");
    return 0;
}
