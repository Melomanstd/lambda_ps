#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{
    bStop = false;
}

void Thread::run()
{
    QByteArray ip=scIP.toAscii();
    openSocket(ip.data(),"8003");
    msleep(100);
    SET_OUTPUT_STATE_F(0);
    bStop = false;
    double par1=0;
    double par2=0;
    QString par3;
    while(!bStop)
    {
        QString sss = QString(FIRMWARE_REVISION_F());
        if (!sss.contains("LAMBDA"))
        {
            emit connectionLost();
            break;
        }

//        if(!queue.isEmpty())
//        {
//            processingQueue();
//            continue;
//        }

        par1 = QString(MEAS_VOLTAGE_F()).toDouble();
        par2 = QString(MEAS_CURRENT_F()).toDouble();

        if(bStop) break;
        emit stateUpdate(par1, par2, par3);
//        msleep(500);
        m_wait.wait(&mutex, 500);
    }
    closeSocket();
}

void Thread::stopThread()
{
    mutex.lock();
    bStop = true;
    mutex.unlock();
}

void Thread::sendingCommand(bool s)
{
}

void Thread::setSocketIp(QString s)
{
    scIP = s;
}

void Thread::resumeThread()
{
    m_wait.wakeAll();
}

void Thread::processingQueue()
{
#ifdef asd
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
        }
        queue.pop_front();
        delete item;
    }
#endif
}

void Thread::addCommand(int cmdNum, QString param)
{
//    queue.push_back(new QueueItem(cmdNum, param));
}
