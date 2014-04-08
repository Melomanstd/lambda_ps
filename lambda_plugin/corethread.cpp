#include "corethread.h"

CoreThread::CoreThread(QObject *parent) :
    QThread(parent)
{
    oVolt=0;
    uVolt=0;
    voltage=0;
    current=0;
    startedFromGUI=false;
}

CoreThread::~CoreThread()
{
    closeSocket();
}

void CoreThread::run()
{
    QString s;
    QByteArray i;
    QByteArray p;
    if(startedFromGUI)
    {
        i = ip.toAscii();
        p = port.toAscii();
    }
    else
    {
        QSettings s("lambdaconf.ini", QSettings::IniFormat);
        i = s.value("lambda/ip").toByteArray();
        p = "8003";
    }

    if (openSocket(i.data(), p.data()))
        bStop = true;
    else bStop = false;
    emit socketState(!bStop);
    while (!bStop)
    {
        s = FIRMWARE_REVISION_F();
        if(!s.contains("LAMBDA"))
        {
            emit connectionLost();
            break;
        }

        if (!queue.isEmpty())
        {
            processingQueue();
        }

        voltage=QString(MEAS_VOLTAGE_F()).toDouble();
        current=QString(MEAS_CURRENT_F()).toDouble();
        oVolt = QString(GET_OVERVOLT_PROTECTION_F()).toDouble();
        uVolt = QString(GET_UNDERVOLT_LIMIT_F()).toDouble();
        if(bStop) break;
        m_wait.wait(&mutex, 500);
    }
    closeSocket();
    startedFromGUI=false;
}

int CoreThread::startThread(QString ip, QString port)
{
    this->ip = ip;
    this->port = port;
//    QByteArray cIp = ip.toAscii();
//    QByteArray cPort = port.toAscii();
//    int res = openSocket(cIp.data(), cPort.data());
//    if(!res)
    startedFromGUI=true;
    start();
    return 0;
}

void CoreThread::stopThread()
{
    mutex.lock();
    bStop = true;
    mutex.unlock();
}

void CoreThread::resumeThread()
{
    m_wait.wakeAll();
}

double CoreThread::getVoltage()
{
//    mutex.lock();
    return voltage;
//    mutex.unlock();
}

double CoreThread::getCurrent()
{
//    mutex.lock();
    return current;
//    mutex.unlock();
}

void CoreThread::processingQueue()
{
    while(!queue.isEmpty())
    {
        QueueItem *item = queue.first();
        switch (item->cmdNum)
        {
        case SET_VOLT_LIMIT:
            SET_VOLT_LIMIT_F(item->param.toDouble());
            break;
        case SET_CURR_LIMIT:
            SET_CURR_LIMIT_F(item->param.toDouble());
            break;
        case SET_UNDERVOLT_LIMIT:
            SET_UNDERVOLT_LIMIT_F(item->param.toDouble());
            break;
        case SET_OVERVOLT_PROTECTION:
            SET_OVERVOLT_PROTECTION_F(item->param.toDouble());
            break;
        case SET_OUTPUT_STATE:
            SET_OUTPUT_STATE_F(item->param.toInt());
            break;
        case SET_SETTING_MODE:
            SET_SETTING_MODE_F(item->param.toInt());
            break;
        case SET_START_MODE:
            SET_START_MODE_F(item->param.toInt());
            break;
        case SET_FOLDBACK_PROTECTION:
            SET_FOLDBACK_PROTECTION_F(item->param.toInt());
            break;
        case GET_OUTPUT_STATE:
            item->result = QString(GET_OUTPUT_STATE_F());
            break;
        case GET_FOLDBACK_PROTECTION:
            item->result = QString(GET_FOLDBACK_PROTECTION_F());
            break;
        case GET_START_MODE:
            item->result = QString(GET_START_MODE_F());
            break;
        case GET_SETTING_MODE:
            item->result = QString(GET_SETTING_MODE_F());
            break;
        case GET_OVERVOLT_PROTECTION:
            item->result = QString(GET_OVERVOLT_PROTECTION_F());
            break;
        case GET_UNDERVOLT_LIMIT:
            item->result = QString(GET_UNDERVOLT_LIMIT_F());
            break;
        }
        item->wait.wakeAll();
        queue.pop_front();
//        delete item;
    }
}

void CoreThread::addRequest(QueueItem *item)
{
//    mutex.lock();
    while (!mutex.tryLock())
        msleep(50);
    queue.push_back(item);
    mutex.unlock();
}
